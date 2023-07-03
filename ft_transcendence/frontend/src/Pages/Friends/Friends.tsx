import _ from "lodash";
import "react-data-grid/lib/styles.css";
import { useContext, useEffect, useMemo, useState } from "react";
import { UsersContext } from "../../Context/UsersContext";
import "./Friends.css";
import { User, UserStatus, useAuth } from "../../Context/AuthContext";
import Tabs from "react-bootstrap/Tabs";
import Tab from "react-bootstrap/Tab";
import Header from "../../Navigation/Header/Header";
import { Col, Container, Row } from "react-bootstrap";
import AvatarImg from "./../../Images/Avatar.jpg";
import { Socket } from "socket.io-client";
import { WebSocketContext } from "../../Context/WebSocketContext";
import Sidebar from "../../Navigation/Sidebar/Sidebar";
import Dropdown from "react-bootstrap/Dropdown";

import MoreIcon from "./../../Images/More.svg";

type FilterType = "all" | "friends" | "online" | "playing" | "banned" | "invitation";

function checkOnline(isOnline: boolean) {
  if (isOnline) {
    return (
      <>
        <div className="online-status-friends-page" />
      </>
    );
  }
}

enum Status {
  Offline,
  Online,
  Playing,
}

type UsersTableProps = {
  users: User[];
  handleNewFriend: (id: string) => void;
  handleRemoveFriend: (id: string) => void;
  handleBan: (id: string) => void;
  handleUnban: (id: string) => void;
  handleRemoveFriendRequest: (id: string) => void;
  handleAcceptFriendRequest: (id: string) => void;
  handleRefuseFriendRequest: (id: string) => void;
};

const UsersTable: React.FC<UsersTableProps> = ({
  users,
  handleNewFriend,
  handleRemoveFriend,
  handleBan,
  handleUnban,
  handleRemoveFriendRequest,
  handleAcceptFriendRequest,
  handleRefuseFriendRequest,
}) => (
  <Row>
    {users.map((user) => (
      <Col lg="4">
        <Col key={user.id} className="friends-inline-user user-row-bottom friends-mob-card">
          <Col className="friends-inline-user" md="8">
            <div>
              <Col lg={12} xl={3} className="padding-zero image-container friends-container-img">
                <img
                  alt=""
                  src={user.avatar ?? AvatarImg}
                  width="40"
                  height="40"
                  className="avatar-friends d-inline-block align-top friends-avatar-mob"
                  id="navbarScrollingDropdown"
                />
                {checkOnline(user.status === UserStatus.ONLINE || user.status === UserStatus.PLAYING)}
              </Col>
            </div>
            <div className="username-margin friends-nickname-mob">
              <h1>{user.username}</h1>
            </div>
            {/* <h1> {Status[user.status]} </h1> */}
          </Col>
          <Col className="col-tight-al" md="4">
            <Dropdown className="menu-toogle margin-panel-chat-settings">
              <Dropdown.Toggle variant="" id="dropdown-basic">
                <img
                  alt=""
                  src={MoreIcon}
                  width="20"
                  height="20"
                  className="d-inline-block align-top sidebar-icon"
                />
              </Dropdown.Toggle>
              <Dropdown.Menu className="chat-dropdown-style">
                {!user.isFriend &&
                  !user.friendshipRequestSent &&
                  !user.isBanned &&
                  !user.hasBanned &&
                  !user.friendshipRequestReceived && (
                    <Dropdown.Item
                      className="chat-drop-menu-item"
                      onClick={() => handleNewFriend(user.id)}
                    >
                      <div className="box-with-icon">
                        {/* <div><img alt="" src={AddFriendIcon} width="20" height="20" className="sidebar-icon dropdown-icon-button" /></div> */}
                        <div className="dropdown-name-button">Add friend</div>
                      </div>
                    </Dropdown.Item>
                  )}
                {user.friendshipRequestSent && (
                  <Dropdown.Item
                    className="chat-drop-menu-item"
                    onClick={() => handleRemoveFriendRequest(user.id)}
                  >
                    <div className="box-with-icon">
                      {/* <div><img alt="" src={RemoveInvitationIcon} width="20" height="20" className="sidebar-icon dropdown-icon-button" /></div> */}
                      <div className="dropdown-name-button">
                        Cancel invitation
                      </div>
                    </div>
                  </Dropdown.Item>
                )}
                {user.isFriend && (
                  <Dropdown.Item
                    className="chat-drop-menu-item"
                    onClick={() => handleRemoveFriend(user.id)}
                  >
                    <div className="box-with-icon">
                      {/* <div><img alt="" src={RemoveFriendIcon} width="20" height="20" className="sidebar-icon dropdown-icon-button" /></div> */}
                      <div className="dropdown-name-button">Remove friend</div>
                    </div>
                  </Dropdown.Item>
                )}
                {!user.isBanned && (
                  <Dropdown.Item
                    className="chat-drop-menu-item"
                    onClick={() => handleBan(user.id)}
                  >
                    <div className="box-with-icon">
                      {/* <div><img alt="" src={BanIcon} width="20" height="20" className="sidebar-icon dropdown-icon-button" /></div> */}
                      <div className="dropdown-name-button">Ban user</div>
                    </div>
                  </Dropdown.Item>
                )}
                {user.isBanned && (
                  <Dropdown.Item
                    className="chat-drop-menu-item"
                    onClick={() => handleUnban(user.id)}
                  >
                    <div className="box-with-icon">
                      {/* <div><img alt="" src={UnbanIcon} width="20" height="20" className="sidebar-icon dropdown-icon-button" /></div> */}
                      <div className="dropdown-name-button">Unban user</div>
                    </div>
                  </Dropdown.Item>
                )}
                {user.friendshipRequestReceived && (
                  <div>
                    <Dropdown.Item
                      className="chat-drop-menu-item"
                      onClick={() => handleAcceptFriendRequest(user.id)}
                    >
                      <div className="box-with-icon">
                        {/* <div><img alt="" src={AcceptIcon} width="20" height="20" className="sidebar-icon dropdown-icon-button" /></div> */}
                        <div className="dropdown-name-button">
                          Accept invitation
                        </div>
                      </div>
                    </Dropdown.Item>
                    <Dropdown.Item
                      className="chat-drop-menu-item"
                      onClick={() => handleRefuseFriendRequest(user.id)}
                    >
                      <div className="box-with-icon">
                        <div className="dropdown-name-button">
                          Refuse invitation
                        </div>
                      </div>
                    </Dropdown.Item>
                  </div>
                )}
              </Dropdown.Menu>
            </Dropdown>
          </Col>
        </Col>
      </Col>
    ))}
  </Row>
);

function FriendsBlock() {
  const socket = useContext<Socket | undefined>(WebSocketContext);
  const { user } = useAuth();
  const users = useContext(UsersContext);
  const [selectedFilter, setSelectedFilter] = useState<FilterType>("all");
  const usersVisible = useMemo(() => (
    users
      .filter((u) => !u.hasBanned)
      .filter((u) => u.id !== user?.id)
  ), [users, user]);
  const [usersList, setUsersList] = useState<User[]>(usersVisible);

  const filterFunctions = useMemo(() => ({
    all: (u: User) => true,
    friends: (u: User) => u.isFriend,
    online: (u: User) => u.status === UserStatus.ONLINE,
    playing: (u: User) => u.status === UserStatus.PLAYING,
    banned: (u: User) => u.isBanned,
    invitation: (u: User) => u.friendshipRequestReceived,
  }), []);

  const counts = _(filterFunctions)
    .map((filterFunction, key) => ({
      key,
      count: usersVisible.filter(filterFunction).length,
    }))
    .keyBy("key")
    .value();

  useEffect(() => {
    setUsersList(
      usersVisible.filter((u) => filterFunctions[selectedFilter](u))
    );
  }, [filterFunctions, selectedFilter, usersVisible]);

  const handleNewFriend = (recipientId: string) => {
    if (user) {
      socket?.emit("newfriendrequest", {
        senderId: user.id,
        recipientId: recipientId,
      });
    }
  };

  const handleRemoveFriend = (recipientId: string) => {
    if (user) {
      socket?.emit("removefriend", {
        senderId: user.id,
        recipientId: recipientId,
      });
    }
  };
  <Tab
  eventKey="online"
  title={
    <>
      Online
      <div className="mini-badge-friends">
        {counts["online"].count}
      </div>
    </>
  }
  className="friends-table"
></Tab>
  const handleBan = (recipientId: string) => {
    if (user) {
      socket?.emit("banuser", {
        punisherId: user.id,
        recipientId: recipientId,
      });
    }
  };

  const handleUnban = (recipientId: string) => {
    if (user) {
      socket?.emit("cancelban", {
        punisherId: user.id,
        recipientId: recipientId,
      });
    }
  };

  const handleRemoveFriendRequest = (recipientId: string) => {
    if (user) {
      socket?.emit("cancelfriendrequest", {
        senderId: user.id,
        recipientId: recipientId,
      });
    }
  };

  const handleAcceptFriendRequest = (recipientId: string) => {
    if (user) {
      socket?.emit("acceptfriendrequest", {
        senderId: recipientId,
        recipientId: user.id,
      });   <Tab
      eventKey="online"
      title={
        <>
          Online
          <div className="mini-badge-friends">
            {counts["online"].count}
          </div>
        </>
      }
      className="friends-table"
    ></Tab>
    }
  };

  const handleRefuseFriendRequest = (senderId: string) => {
    if (user) {
      socket?.emit("refusefriendrequest", {
        senderId: senderId,
        recipientId: user.id,
      });
    }
  };

  return (
    <>
      <Container>
        <div className="friends-area">
          <Tabs defaultActiveKey="all" id="uncontrolled-tab-example" onSelect={(k) => setSelectedFilter(k as FilterType)}>
            <Tab
              eventKey="all"
              title={
                <>
                  All users
                  <div className="mini-badge-friends">
                    {counts["all"].count}
                  </div>
                </>
              }
              className="friends-table"
            ></Tab>
            <Tab
              eventKey="online"
              title={
                <>
                  Online
                  <div className="mini-badge-friends">
                    {counts["online"].count}
                  </div>
                </>
              }
              className="friends-table"
            ></Tab>
               <Tab
              eventKey="playing"
              title={
                <>
                  Playing
                  <div className="mini-badge-friends">
                    {counts["playing"].count}
                  </div>
                </>
              }
              className="friends-table"
            ></Tab>
            <Tab
              eventKey="friends"
              title={
                <>
                  Friends
                  <div className="mini-badge-friends">
                    {counts["friends"].count}
                  </div>
                </>
              }
              className="friends-table"
            ></Tab>
            <Tab
              eventKey="banned"
              title={
                <>
                  Banned
                  <div className="mini-badge-friends">
                    {counts["banned"].count}
                  </div>
                </>
              }
              className="friends-table"
            ></Tab>
            <Tab
              eventKey="invitation"
              title={
                <>
                  Invitations
                  <div className="mini-badge-friends">
                    {counts["invitation"].count}
                  </div>
                </>
              }
              className="friends-table"
            ></Tab>
          </Tabs>
          <UsersTable
            users={usersList}
            handleNewFriend={handleNewFriend}
            handleRemoveFriend={handleRemoveFriend}
            handleBan={handleBan}
            handleUnban={handleUnban}
            handleRemoveFriendRequest={handleRemoveFriendRequest}
            handleAcceptFriendRequest={handleAcceptFriendRequest}
            handleRefuseFriendRequest={handleRefuseFriendRequest}
          />
        </div>
      </Container>
    </>
  );
}

function Friends() {
  return (
    <>
      <Header />
      <Container>
        <Row className="zero-margin">
          <Col lg={12} xl={2} className="sidebar-global">
            <Sidebar />
          </Col>
          <Col lg={12} xl={10}>
            <div className="content">
              <Row>
                <Col xl={12}>
                  <div className="inline">
                    <div className="left">
                      <h1 className="heading heading-margin">Friends</h1>
                    </div>
                  </div>
                </Col>
              </Row>
              <Row>
                <Col
                  xl={12}
                  className="margin-card"
                  style={{ marginBottom: "30px" }}
                >
                  <FriendsBlock />
                </Col>
              </Row>
            </div>
          </Col>
        </Row>
      </Container>
    </>
  );
}

export default Friends;
