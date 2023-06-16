import _ from "lodash";
import {
  createContext,
  useEffect,
  useState,
  useContext,
  useMemo,
  ReactNode,
} from "react";
import { WebSocketContext } from "./WebSocketContext";
import { useAuth } from "./AuthContext";

/**
 * An interface that represents a message in the database.
 */
export interface MessageDB {
  message: string;
  from: string;
  toUserId?: string;
  toChannelId?: string;
  date: Date;
}

/**
 * An interface that represents a user message.
 */
export interface UserMessage {
  date: Date;
  message: string;
  from: string;
  toUserId?: string;
}

/**
 * An interface that represents a channel message.
 */
export interface ChannelMessage {
  date: Date;
  message: string;
  from: string;
  toChannelId?: string;
}

/**
 * An interface that represents user conversations.
 */
export interface UserConversations {
  [key: string]: UserMessage[];
}

/**
 * An interface that represents channel conversations.
 */
export interface ChannelConversations {
  [key: string]: ChannelMessage[];
}

/**
 * An interface that represents the message store.
 */
export interface MessageStore {
  users?: UserConversations;
  channels?: ChannelConversations;
}

/**
 * Context for storing messages.
 */
export const MessagesContext = createContext<MessageStore>({});

/**
 * Create a new message store.
 * @param {MessageDB[]} messages - The messages from the database.
 * @param {string} userId - The id of the current user.
 * @returns A new message store.
 */
function createStore(messages: MessageDB[], userId: string): MessageStore {
  const received = _(messages)
    .filter(
      ({ toUserId }: MessageDB): boolean =>
      toUserId !== undefined && toUserId !== userId
    )
    .groupBy("toUserId")
    .value();
  const sent = _(messages)
    .filter(
      ({ toUserId, from }: MessageDB): boolean =>
      toUserId !== undefined && from !== userId
    )
    .groupBy("from")
    .value();
  const customMerge = (a: any, b: any) =>
    _.isArray(a) ? a.concat(b) : undefined;
  const users = _.mergeWith(received, sent, customMerge);
  const channels = _(messages).filter("toChannelId").groupBy("toChannelId").value();
  return { users, channels };
}

/**
 * Add a message to a message store.
 * @param {MessageDB} message - The message to add.
 * @param {MessageStore} store - The current message store.
 * @param {string} userId - The id of the current user.
 * @returns An updated message store.
 */
function addToStore(
  message: MessageDB,
  store: MessageStore,
  userId: string
): MessageStore {
  const { from, toUserId, toChannelId } = message;
  if (toUserId) {
    const keyUser = from === userId ? toUserId : from;
    const userMessages = _.get(store, `users.${keyUser}`, []);
    return {
      ...store,
      users: {
        ..._.get(store, "users", {}),
        [keyUser]: [...userMessages, message],
      },
    };
  }
  if (toChannelId) {
    const channelMessages = _.get(store, `channels.${toChannelId}`, []);
    return {
      ...store,
      channels: {
        ..._.get(store, "channels", {}),
        [toChannelId]: [...channelMessages, message],
      },
    };
  }
  return store;
}

/**
 * The provider component for the MessagesContext.
 * @param {ReactNode} children - The child components.
 * @returns The MessagesContext provider component.
 */
function MessagesProvider({ children }: { children: ReactNode }): React.JSX.Element {
  const socket = useContext(WebSocketContext);
  const { user } = useAuth();
  const [messageStore, setMessageStore] = useState<MessageStore>({});
  useEffect(() => {
    socket?.on("allmessages", (messages: MessageDB[]) => {
      if (user) setMessageStore(createStore(messages, user.id));
    });
    socket?.on("newmessage", (message: MessageDB) => {
      if (user) setMessageStore((currentMessages) =>
         addToStore(message, currentMessages, user.id)
      )});
    if (user) socket?.emit("allmessages", { userId: user.id });
    return () => {
      socket?.off("allmessages");
      socket?.off("newmessage");
    };
  }, [socket, user]);
  const value = useMemo(() => messageStore, [messageStore]);
  return (
    <MessagesContext.Provider value={value}>
      {children}
    </MessagesContext.Provider>
  );
}

export default MessagesProvider;
