import { useContext, useState } from "react";
import { WebSocketContext } from "../../Context/WebSocketContext";
import { Socket } from "socket.io-client";
import OverlayTrigger from "react-bootstrap/OverlayTrigger";
import Tooltip from "react-bootstrap/Tooltip";
import AlertIcon from "./../../Images/Alert.svg";
import { useAuth } from "../../Context/AuthContext";
import "./Chat.css";

/**
 * The `ChannelCreation` component provides an interface for creating a new channel.
 * It captures the details for the new channel including name, privacy, and password.
 *
 * @param {() => void} onClose - A function to close the creation form.
 * @returns {JSX.Element} Returns a React element.
 */

function AlertInfo(alertMessage: string) {
  return (
    <>
      <OverlayTrigger
        key={"left"}
        placement={"left"}
        overlay={<Tooltip id={`tooltip-${"left"}`}>{alertMessage}</Tooltip>}
      >
        <div className="right">
          <img
            alt=""
            src={AlertIcon}
            width="20"
            height="20"
            id="navbarScrollingDropdown"
          />
        </div>
      </OverlayTrigger>
    </>
  );
}

function ChannelCreation({
  onClose,
}: {
  onClose: () => void;
}): React.JSX.Element {
  const [name, setName] = useState<string>("");
  const [secret, setSecret] = useState<boolean>(false);
  const [password, setPassword] = useState<string>("");
  const [checkboxClass, setCheckboxClass] = useState<string>(
    "chat-popup-checkbox"
  );
  const socket = useContext<Socket | undefined>(WebSocketContext);
  const { user } = useAuth();

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    if (secret) setPassword("");
    if (user)
      socket?.emit("newchannel", {
        name,
        secret,
        password,
        ownerId: user.id,
      });
    onClose();
  };

  return (
    <div className="chat-popup-window">
      <h4 className="chat-popup-big-head">Create new channel</h4>
      <form onSubmit={handleSubmit}>
        <div className="chat-full-width">
          <div className="chat-popup-head chat-popup-top-margin">
            Channel Name:
          </div>
          <input
            type="text"
            value={name}
            className="chat-popup-input-text"
            onChange={(e) => {
              setName(e.target.value);
            }}
            required
          />
        </div>
        {!secret && (
          <div className="chat-full-width">
            <div className="chat-popup-head chat-popup-top-margin">
              Password:
            </div>
            <input
              type="password"
              value={password}
              className="chat-popup-input-text"
              onChange={(e) => setPassword(e.target.value)}
            />
          </div>
        )}
        <div className="chat-full-width">
          <div className="chat-popup-head chat-popup-top-margin">
            <div>Private:</div>
            <div className="tooltip-popup">
              {AlertInfo("Select if you want to create a private channel")}
            </div>
          </div>
          <div
            className={checkboxClass}
            onClick={() => {
              setSecret((prevState) => !prevState);
              checkboxClass === "chat-popup-checkbox"
                ? setCheckboxClass("chat-popup-checkbox-changed")
                : setCheckboxClass("chat-popup-checkbox");
            }}
          >
            <input
              type="checkbox"
              checked={secret}
              style={{ marginRight: "15px" }}
            />
            Invite only
          </div>
        </div>
        <div style={{ marginTop: "45px", display: "flex" }}>
          <button className="chat-popup-button-blue" type="submit">
            Create
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

export default ChannelCreation;
