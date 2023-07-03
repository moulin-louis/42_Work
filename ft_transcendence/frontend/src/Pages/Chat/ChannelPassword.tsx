import { useContext, useState } from "react";
import { WebSocketContext } from "../../Context/WebSocketContext";
import { Socket } from "socket.io-client";
import { Channel } from "../../Context/ChannelContext";
import "./Chat.css";

/**
 * Component for changing or adding a password to a channel
 * @param {() => void} onClose - Function to call when the modal is to be closed
 * @param {Channel} channel - Channel for which the password is to be changed or added
 * @returns {JSX.Element} The rendered component
 */
function ChannelPassword({
  onClose,
  channel,
}: {
  onClose: () => void;
  channel?: Channel;
}): React.JSX.Element {
  const socket = useContext<Socket | undefined>(WebSocketContext);
  const [password, setPassword] = useState<string>("");
  const handleSubmit = (e: React.FormEvent): void => {
    e.preventDefault();
    if (channel?.id)
      socket?.emit("changechannelpassword", {
        id: channel?.id,
        password,
      });
    onClose();
  };

  return (
    <div className="chat-popup-window">
      <h4 className="chat-popup-big-head">Change password</h4>
      <form onSubmit={handleSubmit}>
        <div className="chat-full-width">
          <div className="chat-popup-head chat-popup-top-margin">Password:</div>
          <input
            type="password"
            value={password}
            className="chat-popup-input-text"
            onChange={(e) => setPassword(e.target.value)}
          />
        </div>
        <div style={{ marginTop: "45px", display: "flex" }}>
          <button className="chat-popup-button-blue" type="submit">
            {channel?.protected ? "Change Password" : "Add Password"}
          </button>
          <button
            className="chat-popup-button-white"
            type="button"
            onClick={onClose}
          >
            Cancel
          </button>
        </div>
      </form>
    </div>
  );
}

export default ChannelPassword;
