import _ from "lodash";
import React, {
  createContext,
  useContext,
  useEffect,
  useState,
  useMemo,
  ReactNode,
} from "react";
import { WebSocketContext } from "./WebSocketContext";
import {
  ChannelConversations,
  ChannelMessage,
  MessageStore,
  MessagesContext,
  UserConversations,
  UserMessage,
} from "./ChatContext";
import { useAuth } from "./AuthContext";
import { ChannelContext } from "./ChannelContext";

/**
 * An interface that represents the last read message.
 */
interface LastRead {
  from: string;
  toUserId?: string;
  toChannelId?: string;
  date: Date;
}

/**
 * An interface that represents the count of unread messages.
 */
export interface UnreadStore {
  lastRead?: LastRead[];
  countByUsers?: { userId: string; unread: number }[];
  countByChannels?: { channelId: string; unread: number }[];
  unread?: number;
}

/**
 * Context for storing the count of unread messages.
 */
export const UnreadContext = createContext<UnreadStore>({});

/**
 * Count the number of unread messages by users.
 * @param {UserConversations | undefined} conversations - User conversations.
 * @param {LastRead[] | undefined} lastReads - Last read messages.
 * @returns An array of unread message counts by user.
 */
function countUnreadMessagesByUsers(
  conversations: UserConversations | undefined,
  lastReads: LastRead[] | undefined
): { userId: string; unread: number }[] {
  const checkIfRead = (date: Date, toUserId: string): boolean => {
    const lastRead = _(lastReads).find({ toUserId })?.date;
    return lastRead ? date > lastRead : true;
  };
  return _(conversations)
    .map((messages: UserMessage[], userId: string) => ({
      userId,
      unread: _(messages)
        .filter(({ date }: UserMessage) => checkIfRead(date, userId))
        .size(),
    }))
    .value();
}

/**
 * Count the number of unread messages by channels.
 * @param {ChannelConversations | undefined} conversations - Channel conversations.
 * @param {LastRead[] | undefined} lastReads - Last read messages.
 * @returns An array of unread message counts by channel.
 */
function countUnreadMessagesByChannels(
  conversations: ChannelConversations | undefined,
  lastReads: LastRead[] | undefined
): { channelId: string; unread: number }[] {
  const checkIfRead = (date: Date, toChannelId: string): boolean => {
    const lastRead = _(lastReads).find({ toChannelId })?.date;
    return lastRead ? date > lastRead : true;
  };
  return _(conversations)
    .map((messages: ChannelMessage[], channelId: string) => ({
      channelId,
      unread: _(messages)
        .filter(({ date }: ChannelMessage) => checkIfRead(date, channelId))
        .size(),
    }))
    .value();
}

/**
 * Add the count of unread messages to the message store.
 * @param {MessageStore} messageStore - The message store.
 * @param {LastRead[]} lastReads - The last read messages.
 * @returns The updated unread message store.
 */
function addCounts(
  messageStore: MessageStore,
  lastReads: LastRead[],
  bannedChannels: string[]
): UnreadStore {
  const countByUsers = countUnreadMessagesByUsers(
    messageStore.users,
    lastReads
  );
  const countByChannels = countUnreadMessagesByChannels(
    _.omit(messageStore.channels, bannedChannels),
    lastReads
  );
  const res = {
    lastReads,
    countByUsers,
    countByChannels,
    unread:
      _(countByUsers).map("unread").sum() +
      _(countByChannels).map("unread").sum(),
  };
  if (res.unread) document.title = `PingPong42 [${res.unread}]`;
  else document.title = "PingPong42";
  return res;
}

/**
 * The provider component for the UnreadContext.
 * @param {ReactNode} children - The child components.
 * @returns The UnreadContext provider component.
 */
function UnreadProvider({
  children,
}: {
  children: ReactNode;
}): React.JSX.Element {
  const socket = useContext(WebSocketContext);
  const { user } = useAuth();
  const channels = useContext(ChannelContext);
  const [unreadStore, setUnreadStore] = useState<UnreadStore>({});
  const messageStore: MessageStore = useContext(MessagesContext);

  useEffect(() => {
    const bannedChannels = _(channels)
      .filter((c) => c.bans?.includes(user?.id ?? ""))
      .map("id")
      .value();
    socket?.on("allread", (lastReads: LastRead[]) => {
      setUnreadStore(addCounts(messageStore, lastReads, bannedChannels));
    });
    if (user) socket?.emit("allread", { userId: user.id });
    return () => {
      socket?.off("allread");
    };
  }, [socket, user, messageStore, channels]);

  const value = useMemo(() => unreadStore, [unreadStore]);

  return (
    <UnreadContext.Provider value={value}>{children}</UnreadContext.Provider>
  );
}

export default UnreadProvider;
