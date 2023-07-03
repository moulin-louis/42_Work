import AvatarImg from "./../../Images/Avatar.jpg";
import { User, useAuth } from "../../Context/AuthContext";
import "./Chat.css";
import { useContext } from "react";
import { WebSocketContext } from "../../Context/WebSocketContext";
import { Socket } from "socket.io-client";
import { HistoryMini } from "../History/HistoryMini";
import { AchievementsMini } from "../Achievements/AchievementsMini";
import CloseImg from "./../../Images/Close.svg";


/**
 * A React component to display user profile information.
 *
 * @param {Object} props - Component properties
 * @param {Function} props.onClose - Function to close the profile popup
 * @param {User} props.user - User object containing user data
 *
 * @returns {React.JSX.Element} Rendered user profile
 */
function UserProfile({
  onClose,
  friend,
}: {
  onClose: () => void;
  friend: User;
}): React.JSX.Element {
  const socket = useContext<Socket | undefined>(WebSocketContext);
  const { user } = useAuth();
  function handleNewFriend(id: string): void {
    if (friend) {
      socket?.emit("newfriendrequest", {
        senderId: user?.id,
        recipientId: id,
      });
    }
  }

  function handleRemoveFriendRequest(id: string): void {
    if (user) {
      socket?.emit("cancelfriendrequest", {
        senderId: user.id,
        recipientId: id,
      });
    }
  }

  function handleRemoveFriend(id: string): void {
    if (user) {
      socket?.emit("removefriend", {
        senderId: user.id,
        recipientId: id,
      });
    }
  }

  function handleAcceptFriendRequest(id: string): void {
    if (user) {
      socket?.emit("acceptfriendrequest", {
        senderId: id,
        recipientId: user.id,
      });
    }
  }

  function handleRefuseFriendRequest(id: string): void {
    if (user) {
      socket?.emit("refusefriendrequest", {
        senderId: id,
        recipientId: user.id,
      });
    }
  }



  return (
    <div className="chat-popup-window chat-popup-profile-window padding-pop-profile">
      <img alt=""
        src={CloseImg}
        width="30"
        height="30"
        className="close-btn"
        id="navbarScrollingDropdown"
        onClick={onClose}
      />
      <div className="row">
        <div className="col-lg-1 col-md-12 d-flex flex-column align-items-center user-popup-info-align"></div>
        <div className="col-lg-3 col-md-12 chat-popup-usercard">
          <img alt=""
            src={friend.avatar ?? AvatarImg}
            width="160"
            height="160"
            className="avatar-border d-inline-block align-top"
            id="navbarScrollingDropdown" />

          <h2 className="chat-popup-usercard-text chat-popup-usercard-text-user">{friend.username}</h2>
          <h2 className="chat-popup-usercard-text">{friend.email}</h2>
          <h2 className="chat-popup-usercard-text">
            Win percentage: {friend.matchesPlayed !== 0 ? ((friend.matchesWon / friend.matchesPlayed * 100).toFixed(2) + '%') : '0%'}
          </h2>
          {!friend.isFriend &&
            !friend.friendshipRequestSent &&
            !friend.isBanned &&
            !friend.hasBanned &&
            !friend.friendshipRequestReceived && (
              <button className="chat-popup-button-blue margin-right-popup-button margin-top-bottom-popup" type="button"
                onClick={() => handleNewFriend(friend.id)}>
                Add to Friends
              </button>)}
          {friend.friendshipRequestSent && (
            <button className="chat-popup-button-blue margin-right-popup-button margin-top-bottom-popup red-button" type="button"
              onClick={() => handleRemoveFriendRequest(friend.id)}>
              Cancel invitation
            </button>)}
          {friend.isFriend && (
            <button className="chat-popup-button-blue margin-right-popup-button margin-top-bottom-popup red-button" type="button"
              onClick={() => handleRemoveFriend(friend.id)}>
              Remove from friends
            </button>)}
          {friend.friendshipRequestReceived && (
            <div className="profile-buttons-align-popup ">
              <button className="chat-popup-button-blue margin-right-popup-button margin-top-bottom-popup" type="button"
                onClick={() => handleAcceptFriendRequest(friend.id)}>
                Accept invitation
              </button>
              <button className="chat-popup-button-blue margin-right-popup-button margin-top-bottom-popup red-button" type="button"
                onClick={() => handleRefuseFriendRequest(friend.id)}>
                Refuse invitation
              </button>
            </div>
          )}
          {/* <div>
            <button
              className="chat-popup-button-white chat-popup-space-profile margin-auto-history"
              type="button"
              onClick={onClose}
            >
              Close Popup
            </button>
          </div> */}
        </div>
        <div className="col-lg-1 col-md-12 d-flex flex-column align-items-center user-popup-info-align"></div>
        <div className="col-lg-7 col-md-12 d-flex flex-column user-popup-info-align">
          <div className="heading-profile-popup">
            Last games
          </div>
          <div className="chat-popup-history">
            <HistoryMini id={friend.id} />
          </div>
          <div>
            <a className="chat-popup-button-blue full-width-mob buttons-settings-mob dashboard-button-more" href="/history">
              See all games →
            </a>
          </div>
          <div className="heading-profile-popup margin-small-achievements">
            Achievements
          </div>
          <div className="row">
            <AchievementsMini user={friend} />
          </div>
          <div>
            <a className="chat-popup-button-blue full-width-mob buttons-settings-mob dashboard-button-more" href="/achievements">
              See all achievements →
            </a>
          </div>
        </div>
      </div>
    </div>
  );
}

export default UserProfile;
