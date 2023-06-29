import _ from "lodash";
import { useContext } from "react";
import { WebSocketContext } from "../../Context/WebSocketContext";
import { Socket } from "socket.io-client";
import { Channel } from "../../Context/ChannelContext";
import { UsersContext } from "../../Context/UsersContext";
import { User } from "../../Context/AuthContext";

/**
 * A React component for managing the members of a channel.
 * This includes functionalities such as muting, banning, unbanning, and making a user admin.
 *
 * @param {Object} props - The properties passed to the component
 * @param {Function} props.onClose - Function to close the management window
 * @param {Channel} [props.channel] - The channel currently being managed
 * @param {boolean} props.owner - If the current user is the owner of the channel
 *
 * @returns {JSX.Element} The rendered ChannelManagement component
 */
function ChannelManagement({
  onClose,
  channel,
  owner,
}: {
  onClose: () => void;
  channel?: Channel;
  owner: boolean;
}) {
  const socket = useContext<Socket | undefined>(WebSocketContext);
  const users = useContext(UsersContext);
  const getUser = (id: string) => users.find((u: User) => u.id === id);

  const muteMember = (userId: string, channelId?: string) => {
    socket?.emit("mutefromchannel", { userId, channelId });
  };

  const banMember = (userId: string, channelId?: string) => {
    socket?.emit("banfromchannel", { userId, channelId });
  };

  const unbanMember = (userId: string, channelId?: string) => {
    socket?.emit("unbanfromchannel", { userId, channelId });
  };

  const makeAdmin = (userId: string, channelId?: string) => {
    socket?.emit("addadmintochannel", { userId, channelId });
  };

  const removeAdmin = (userId: string, channelId?: string) => {
    socket?.emit("removeadminfromchannel", { userId, channelId });
  };

  const members = channel?.members ?? [];

  const isAdmin = (userId: string) => channel?.admins?.includes(userId);
  const isMuted = (userId: string) => channel?.mutes?.includes(userId);
  const isOwner = (userId: string) => channel?.owner?.includes(userId);
  const isBanned = (userId: string) => channel?.bans?.includes(userId);

  return (
    <div className="chat-popup-window">
      <h4 className="chat-popup-big-head">Manage members</h4>
      <div className="mob-scroll-settings">
        {_(members)
          .map(getUser)
          .filter(Boolean)
          .map((m: User) => (
            <div className="chat-popup-inline" key={m.id}>
              <div className="box-with-icon">
                {m.username}
                {isOwner(m.id) && <div className="mini-bage-admin">Owner</div>}
                {!isOwner(m.id) && isAdmin(m.id) && (
                  <div className="mini-bage-admin">Admin</div>
                )}
                {isMuted(m.id) && <div className="mini-bage-admin">Muted</div>}
                {isBanned(m.id) && (
                  <div className="mini-bage-admin">Banned</div>
                )}
              </div>
              <div className="chat-popup-button-margin">
                {!isAdmin(m.id) && !isMuted(m.id) && !isBanned(m.id) && (
                  <button
                    className="mini-button-settings"
                    onClick={() => muteMember(m.id, channel?.id)}
                  >
                    Mute
                  </button>
                )}
                {!isAdmin(m.id) && !isBanned(m.id) && (
                  <button
                    className="mini-button-settings"
                    onClick={() => banMember(m.id, channel?.id)}
                  >
                    Ban
                  </button>
                )}
                {isBanned(m.id) && (
                  <button
                    className="mini-button-settings"
                    onClick={() => unbanMember(m.id, channel?.id)}
                  >
                    Unban
                  </button>
                )}
                {!isAdmin(m.id) && !isBanned(m.id) && (
                  <button
                    className="mini-button-settings"
                    onClick={() => makeAdmin(m.id, channel?.id)}
                  >
                    Make Admin
                  </button>
                )}
                {isAdmin(m.id) && owner && !isOwner(m.id) && (
                  <button
                    className="mini-button-settings"
                    onClick={() => removeAdmin(m.id, channel?.id)}
                  >
                    Remove Admin
                  </button>
                )}
              </div>
            </div>
          ))
          .value()}
      </div>
      <div style={{ marginTop: "45px", display: "flex" }}></div>
      <button
        className="chat-popup-button-white"
        type="button"
        onClick={onClose}
      >
        Cancel
      </button>
    </div>
  );
}

export default ChannelManagement;
