import AvatarImg from "./../../Images/Avatar.jpg";
import { useAuth } from "../../Context/AuthContext";
import { useContext } from "react";
import { HistoryBlock } from "../History/History";
import { UsersContext } from "../../Context/UsersContext";
import Header from "./../../Navigation/Header/Header";
import { AllAchievements } from "../Achievements/Achievements";


/**
 * A React component to display user profile information.
 *
 * @param {Object} props - Component properties
 * @param {Function} props.onClose - Function to close the profile popup
 * @param {User} props.user - User object containing user data
 *
 * @returns {React.JSX.Element} Rendered user profile
 */
function UserProfile(): React.JSX.Element {
    const {user} = useAuth();
    const users = useContext(UsersContext);
    const userConnected = users?.find(u => u.id === user?.id);
  return (
    <>
    { userConnected && (
    <div className="chat-popup-window">
      <div className="row">
        <div className="col-lg-6 col-md-12 d-flex justify-content-center">
          <img alt=""
            src={userConnected.avatar ?? AvatarImg}
            width="160"
            height="160"
            className="avatar-border d-inline-block align-top"
            id="navbarScrollingDropdown" />
        </div>
        <div className="col-lg-6 col-md-12 d-flex flex-column align-items-center user-popup-info-align">
          <h2 className="chat-popup-profile-info">{userConnected.username}</h2>
          <h2 className="chat-popup-profile-info">{userConnected.email}</h2>
          <h2 className="chat-popup-profile-info">Matches play : {userConnected.matchesPlayed}</h2>
          <h2 className="chat-popup-profile-info">Matches won : {userConnected.matchesWon}</h2>
        </div>
        <div>
          <HistoryBlock id={userConnected.id}/>
        </div>
        <div>
          <AllAchievements user={userConnected}/>
        </div>
      </div>
    </div>
    )}
    </>
  );
}

const CurrentUserProfile = () => {
    return (
      <>
        <Header />
        <UserProfile/>
      </>
    );
  }
  

export default CurrentUserProfile;
