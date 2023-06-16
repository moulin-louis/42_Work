import _ from 'lodash';
import "react-data-grid/lib/styles.css";
import { useContext, useState } from "react";
import { UsersContext } from "../../Context/UsersContext";
import './Friends.css';
import { User, UserStatus, useAuth } from "../../Context/AuthContext";
import Tabs from 'react-bootstrap/Tabs';
import Tab from 'react-bootstrap/Tab';
import Header from '../../Navigation/Header/Header';
import { Col, Container, Row } from 'react-bootstrap';
import AvatarImg from "./../../Images/Avatar.jpg";
import { Socket } from 'socket.io-client';
import { WebSocketContext } from '../../Context/WebSocketContext';
import Sidebar from "../../Navigation/Sidebar/Sidebar";
import Dropdown from 'react-bootstrap/Dropdown';

import MoreIcon from "./../../Images/More.svg";

type FilterType = 'all' | 'friends' | 'online' | 'banned' | 'invitation';

type UsersTableProps = {
    users: User[],
    handleNewFriend: (id: string) => void,
    handleRemoveFriend: (id: string) => void,
    handleBan: (id: string) => void,
    handleUnban: (id: string) => void,
    handleRemoveFriendRequest: (id: string) => void,
    handleAcceptFriendRequest: (id: string) => void,
    handleRefuseFriendRequest: (id: string) => void
};

const UsersTable: React.FC<UsersTableProps> = ({ users, handleNewFriend, handleRemoveFriend, handleBan, handleUnban, handleRemoveFriendRequest, handleAcceptFriendRequest, handleRefuseFriendRequest }) => (
    <div>
        <Row className="table-header">
            <Col>
                <strong>User</strong>
            </Col>
            <Col>
                <strong>Username</strong>
            </Col>
            <Col>
                <strong>Status</strong>
            </Col>
            <Col>
                <strong>Actions</strong>
            </Col>
        </Row>
        {users.map((user) =>
            <Row className='friends-inline-user user-row-bottom'>
                <Col className='friends-inline-user'>
                    <div>
                        <img
                            alt=""
                            src={user.avatar ?? AvatarImg}
                            width="40"
                            height="40"
                            className="avatar-friends d-inline-block align-top"
                            id="navbarScrollingDropdown"
                        />
                    </div>
                    <div className='username-margin'>
                        <h1>
                            {user.username}
                        </h1>
                    </div>
                </Col>
                <Col>
                    <div>
                        <h1> {user.username} </h1>
                    </div>
                </Col>
                <Col>
                    <div>
                        <h1> {user.status} </h1>
                    </div>
                </Col>
                <Col>
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
                            {!user.isFriend && !user.friendshipRequestSent && (
                                <Dropdown.Item className="chat-drop-menu-item" onClick={() => handleNewFriend(user.id)}>
                                    <div className="box-with-icon">
                                        {/* <div><img alt="" src={AddFriendIcon} width="20" height="20" className="sidebar-icon dropdown-icon-button" /></div> */}
                                        <div className="dropdown-name-button">Add friend</div>
                                    </div>
                                </Dropdown.Item>
                            )}
                            {user.friendshipRequestSent && (
                                <Dropdown.Item className="chat-drop-menu-item" onClick={() => handleRemoveFriendRequest(user.id)}>
                                    <div className="box-with-icon">
                                        {/* <div><img alt="" src={RemoveInvitationIcon} width="20" height="20" className="sidebar-icon dropdown-icon-button" /></div> */}
                                        <div className="dropdown-name-button">Remove invitation</div>
                                    </div>
                                </Dropdown.Item>
                            )}
                            {user.isFriend && (
                                <Dropdown.Item className="chat-drop-menu-item" onClick={() => handleRemoveFriend(user.id)}>
                                    <div className="box-with-icon">
                                        {/* <div><img alt="" src={RemoveFriendIcon} width="20" height="20" className="sidebar-icon dropdown-icon-button" /></div> */}
                                        <div className="dropdown-name-button">Remove friend</div>
                                    </div>
                                </Dropdown.Item>
                            )}
                            {!user.isBanned && (
                                <Dropdown.Item className="chat-drop-menu-item" onClick={() => handleBan(user.id)}>
                                    <div className="box-with-icon">
                                        {/* <div><img alt="" src={BanIcon} width="20" height="20" className="sidebar-icon dropdown-icon-button" /></div> */}
                                        <div className="dropdown-name-button">Ban user</div>
                                    </div>
                                </Dropdown.Item>
                            )}
                            {user.isBanned && (
                                <Dropdown.Item className="chat-drop-menu-item" onClick={() => handleUnban(user.id)}>
                                    <div className="box-with-icon">
                                        {/* <div><img alt="" src={UnbanIcon} width="20" height="20" className="sidebar-icon dropdown-icon-button" /></div> */}
                                        <div className="dropdown-name-button">Unban user</div>
                                    </div>
                                </Dropdown.Item>
                            )}
                            {user.friendshipRequestReceived && (
                                <div>
                                    <Dropdown.Item className="chat-drop-menu-item" onClick={() => handleAcceptFriendRequest(user.id)}>
                                        <div className="box-with-icon">
                                            {/* <div><img alt="" src={AcceptIcon} width="20" height="20" className="sidebar-icon dropdown-icon-button" /></div> */}
                                            <div className="dropdown-name-button">Accept invitation</div>
                                        </div>
                                    </Dropdown.Item>
                                    <Dropdown.Item className="chat-drop-menu-item" onClick={() => handleRefuseFriendRequest(user.id)}>
                                        <div className="box-with-icon">
                                            {/* <div><img alt="" src={RefuseIcon} width="20" height="20" className="sidebar-icon dropdown-icon-button" /></div> */}
                                            <div className="dropdown-name-button">Refuse invitation</div>
                                        </div>
                                    </Dropdown.Item>
                                </div>
                            )}
                        </Dropdown.Menu>
                    </Dropdown>
                </Col>
            </Row>
        )}
    </div>
);


function FriendsBlock() {
    const [selectedFilter, setSelectedFilter] = useState<FilterType>('all');
    const users = useContext(UsersContext);
    const { user } = useAuth();
    const socket = useContext<Socket | undefined>(WebSocketContext);

    const filterFunctions = {
        'all': (u: User) => true,
        'friends': (u: User) => u.isFriend,
        'online': (u: User) => u.status === UserStatus.ONLINE,
        'banned': (u: User) => u.isBanned,
        'invitation': (u: User) => u.friendshipRequestReceived,
    }

    const usersVisible = users.filter((u) => !u.hasBanned).filter((u) => u.id !== user?.id);
    const usersList = usersVisible.filter(u => filterFunctions[selectedFilter](u));
    const onlineUsersList = usersVisible.filter(u => u.status === UserStatus.ONLINE);
    const counts = _(filterFunctions).map((filterFunction, key) => ({ key, count: usersVisible.filter(filterFunction).length })).keyBy('key').value();

    console.log({ count: counts });

    const handleNewFriend = (recipientId: string) => {
        console.log("new friends");
        if (user) {
            socket?.emit('newfriendrequest', {
                senderId: user.id,
                recipientId: recipientId,
            })
        }
    }

    const handleRemoveFriend = (recipientId: string) => {
        console.log("remove friends");
        if (user) {
            socket?.emit('removefriend', {
                senderId: user.id,
                recipientId: recipientId,
            })
        }
    }

    const handleBan = (recipientId: string) => {
        console.log("ban");
        if (user) {
            socket?.emit('banuser', {
                punisherId: user.id,
                recipientId: recipientId,
            })
        }
    }

    const handleUnban = (recipientId: string) => {
        console.log("unban");
        if (user) {
            socket?.emit('banuser', {
                punisherId: user.id,
                recipientId: recipientId,
            })
        }
    }

    const handleRemoveFriendRequest = (recipientId: string) => {
        console.log("remove friends request");
        if (user) {
            socket?.emit('removefriend', {
                senderId: user.id,
                recipientId: recipientId,
            })
        }
    }

    const handleAcceptFriendRequest = (recipientId: string) => {
        console.log("unban");
        if (user) {
            socket?.emit('acceptfriendrequest', {
                senderId: user.id,
                recipientId: recipientId,
            })
        }
    }

    const handleRefuseFriendRequest = (senderId: string) => {
        console.log("unban");
        if (user) {
            socket?.emit('removefriendrequest', {
                senderId: senderId,
                recipientId: user.id,
            })
        }
    }

    return (
        <>
            <Container>
                <div className="friends-area">
                    <Tabs>
                        <Tab onSelect={() => setSelectedFilter('all')} eventKey="all"
                            title={
                                <>
                                    All users
                                    <div className="mini-badge-friends">{counts["all"].count}</div>
                                </>
                            }
                            className="friends-table"
                        >
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
                        </Tab>
                        <Tab onSelect={() => setSelectedFilter('online')}
                            eventKey="online"
                            title={
                                <>
                                    Online
                                    <div className="mini-badge-friends">{counts["online"].count}</div>
                                </>
                            }
                            className="friends-table"
                        >
                            <UsersTable
                                users={onlineUsersList}
                                handleNewFriend={handleNewFriend}
                                handleRemoveFriend={handleRemoveFriend}
                                handleBan={handleBan}
                                handleUnban={handleUnban}
                                handleRemoveFriendRequest={handleRemoveFriendRequest}
                                handleAcceptFriendRequest={handleAcceptFriendRequest}
                                handleRefuseFriendRequest={handleRefuseFriendRequest}
                            />
                        </Tab>
                        <Tab onSelect={() => setSelectedFilter('friends')}
                            eventKey="friends"
                            title={
                                <>
                                    Friends
                                    <div className="mini-badge-friends">{counts["friends"].count}</div>
                                </>
                            }
                            className="friends-table"
                        ></Tab>
                        <Tab onSelect={() => setSelectedFilter('banned')}
                            eventKey="banned"
                            title={
                                <>
                                    Banned
                                    <div className="mini-badge-friends">{counts["banned"].count}</div>
                                </>
                            }
                            className="friends-table"
                        ></Tab>
                        <Tab onSelect={() => setSelectedFilter('invitation')}
                            eventKey="invitation"
                            title={
                                <>
                                    Invitations
                                    <div className="mini-badge-friends">{counts["invitation"].count}</div>
                                </>
                            }
                            className="friends-table"
                        ></Tab>
                    </Tabs>
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
                                    <div className='inline'>
                                        <div className="left"><h1 className="heading heading-margin">Friends</h1></div>
                                    </div>
                                </Col>
                            </Row>
                            <Row>
                                <Col xl={12} className="margin-card" style={{ marginBottom: "30px" }}>
                                    <FriendsBlock />
                                </Col>
                            </Row>
                        </div>
                    </Col>
                </Row>
            </Container>
        </>
    )
}

export default Friends;