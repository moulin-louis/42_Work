import AvatarImg from "./../../Images/Avatar.jpg";
import { useAuth } from "../../Context/AuthContext";
import { useContext } from "react";
import { HistoryBlock } from "../History/History";
import { UsersContext } from "../../Context/UsersContext";
import Header from "./../../Navigation/Header/Header";
import { AllAchievements } from "../Achievements/Achievements";
import Container from 'react-bootstrap/Container';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';
import Sidebar from './../../Navigation/Sidebar/Sidebar';


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
  const { user } = useAuth();
  const users = useContext(UsersContext);
  const userConnected = users?.find(u => u.id === user?.id);
  return (
    <>
      {userConnected && (
        <div>
          <div className="row">
            <Col xl={4} className="margin-card">
              <div className='statistic-card margin-card auth-shadow'>
                <div className="chat-popup-usercard">
                  <img alt=""
                    src={userConnected.avatar ?? AvatarImg}
                    width="160"
                    height="160"
                    className="avatar-border d-inline-block align-top"
                    id="navbarScrollingDropdown" />

                  <h2 className="chat-popup-usercard-text chat-popup-usercard-text-user">{userConnected.username}</h2>
                  <h2 className="chat-popup-usercard-text">{userConnected.email}</h2>
                  <h2 className="chat-popup-usercard-text">
                    Win percentage: {userConnected.matchesPlayed !== 0 ? ((userConnected.matchesWon / userConnected.matchesPlayed * 100).toFixed(2) + '%') : '0%'}
                  </h2>
                </div>
              </div>
            </Col>
            <Col xl={8} className="margin-card">
              <div className='statistic-card margin-card auth-shadow'>
                <div className="heading-profile-popup">
                  Last games
                </div>
                <div>
                  <HistoryBlock id={userConnected.id} />
                </div>
              </div>
            </Col>
            <Col xl={12} className="margin-card">
              <div className='statistic-card margin-card auth-shadow'>
                <div className="heading-profile-popup">
                  Achievements
                </div>
                <Row>
                  <AllAchievements user={userConnected} />
                </Row>
              </div>
            </Col>
          </div>
        </div>
      )}
    </>
  );
}

function HeadingPage() {
  return (
    <Col xl={12}>
      <div className='inline '>
        <div className="left"><h1 className="heading heading-margin">My Profile</h1></div>
      </div>
    </Col>
  )
}

function Body() {
  const { user } = useAuth();
  const users = useContext(UsersContext);
  const userConnected = users?.find(u => u.id === user?.id);
  return (
    <>
      {userConnected && (
        <Container>
          <Row className="zero-margin">
            <Col lg={12} xl={2} className='sidebar-global'>
              <Sidebar />
            </Col>
            <Col lg={12} xl={10}>
              <div className='content'>
                <Row>
                  <HeadingPage />
                  <UserProfile />
                </Row>
              </div>
            </Col>
          </Row>
        </Container>
      )}
    </>)
}

const CurrentUserProfile = () => {
  return (
    <>
      <Header />
      <Body />
    </>
  );
}


export default CurrentUserProfile;
