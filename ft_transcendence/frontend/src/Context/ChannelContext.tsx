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
import { useAuth } from "./AuthContext";

/**
 * Interface representing a Channel.
 */
export interface Channel {
  admins: string[];
  bans: string[];
  id: string;
  members: string[];
  mutes: string[];
  name: string;
  protected: boolean;
  secret: boolean;
  owner: string;
}

/**
 * Interface representing a ChannelStore.
 */
export interface ChannelStore {
  [key: string]: Channel;
}

/**
 * Context for storing channel data.
 */
export const ChannelContext = createContext<ChannelStore>({});

/**
 * Creates a new ChannelStore.
 * @param {Channel[]} channels - Array of Channel objects.
 * @returns {ChannelStore} The newly created ChannelStore.
 */
function createStore(channels: Channel[]): ChannelStore {
  return _(channels).keyBy("id").value();
}

/**
 * Adds a channel to the ChannelStore.
 * @param {Channel} channel - Channel to be added.
 * @param {ChannelStore} store - The current ChannelStore.
 * @returns {ChannelStore} The updated ChannelStore.
 */
function addToStore(channel: Channel, store: ChannelStore): ChannelStore {
  return { ...store, [channel.id]: channel };
}

/**
 * Deletes a channel from the ChannelStore.
 * @param {string} channelId - The id of the channel to be deleted.
 * @param {ChannelStore} store - The current ChannelStore.
 * @returns {ChannelStore} The updated ChannelStore.
 */
function delFromStore(channelId: string, store: ChannelStore): ChannelStore {
  return _.omit(store, channelId);
}

/**
 * The provider component for the ChannelContext.
 * @param {ReactNode} children - The child components.
 * @returns The ChannelContext provider component.
 */
function ChannelProvider({ children }: { children: ReactNode }): React.JSX.Element {
  const socket = useContext(WebSocketContext);
  const { user } = useAuth();
  const [channelStore, setChannelStore] = useState<ChannelStore>({});

  useEffect(() => {
    socket?.on("allchannels", (channels: Channel[]) => {
      setChannelStore(createStore(channels));
    });
    socket?.on("channel", (channel: Channel) => {
      setChannelStore(store => addToStore(channel, store));
    });
    socket?.on("delchannel", (channelId: string) => {
      setChannelStore(store => delFromStore(channelId, store));
    });
    if (user) socket?.emit("allchannels", { userId: user.id });
    return () => {
      socket?.off("allchannels");
      socket?.off("channel");
    };
  }, [socket, user ]);

  const value = useMemo(() => channelStore, [channelStore]);

  return (
    <ChannelContext.Provider value={value}>{children}</ChannelContext.Provider>
  );
}

export default ChannelProvider;
