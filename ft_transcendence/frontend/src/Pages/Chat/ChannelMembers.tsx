import _ from "lodash";
import { useContext } from "react";
import { Channel } from "../../Context/ChannelContext";
import { WebSocketContext } from "../../Context/WebSocketContext";
import { UsersContext } from "../../Context/UsersContext";

/**
 * Component to display and manage channel members.
 *
 * @param onClose - Function to call when closing the member display
 * @param channel - The channel whose members are being displayed and managed
 */
function ChannelMembers({
  onClose,
  channel,
}: {
  onClose: () => void;
  channel?: Channel;
}) {
  const socket = useContext(WebSocketContext);
  const users = useContext(UsersContext);

  const usersNotInChannel = _(users)
    .filter((u) => !channel?.members.includes(u.id))
    .value();

  const handleAdd = (userId: string) => {
    socket?.emit("joinchannel", {
      userId,
      channelId: channel?.id,
    });
  };

  return (
    <div className="chat-popup-window">
      <h4 className="chat-popup-big-head">Members</h4>
      <div>
        {usersNotInChannel.map((u) => (
          <div className="chat-popup-inline" key={u.id}>
            <div className="margin-right-popup">{u.username}</div>
            <div className="chat-popup-button-margin">
              <button
                className="chat-popup-small-button"
                onClick={() => handleAdd(u.id)}
              >
                Add
              </button>
            </div>
          </div>
        ))}
        <div style={{ marginTop: "45px", display: "flex" }}></div>
        <button
          className="chat-popup-button-white"
          type="button"
          onClick={onClose}
        >
          Cancel
        </button>
      </div>
    </div>
  );
}

export default ChannelMembers;
