import { User } from "../../Context/AuthContext";
import "./Chat.css";

function UserProfile({
  onClose,
  user,
}: {
  onClose: () => void;
  user: User;
}): React.JSX.Element {
  return (
    <div className="chat-popup-window">
      <h4 className="chat-popup-big-head">Profile</h4>
      <h2 className="chat-popup-big-head">{user.username}</h2>
      <h2 className="chat-popup-big-head">{user.email}</h2>
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

export default UserProfile;
