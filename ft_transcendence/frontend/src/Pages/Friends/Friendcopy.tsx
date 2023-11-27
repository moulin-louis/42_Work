import "react-data-grid/lib/styles.css";
import DataGrid from "react-data-grid";
import { useContext, useState } from "react";
import { UsersContext } from "../../Context/UsersContext";
import Header from "../../Navigation/Header/Header";
import { Col, Container, Row } from "react-bootstrap";
import Sidebar from "../../Navigation/Sidebar/Sidebar";
import './Friends.css';

import Tabs from 'react-bootstrap/Tabs';
import Tab from 'react-bootstrap/Tab';

import PlusIcon from "./../../Images/PlusWhite.svg";

import { WebSocketContext } from "../../Context/WebSocketContext";

/**
 * Component to display and add to friends users.
 *
 * @param onClose - Function to call when closing the member display
 * @param users - The users being displayed and managed
 */
function PopupAddFriends({
  onClose,
  users,
}: {
  onClose: () => void;
  users: any[];  // 'any' for simplicity, replace with your user type
}) {
  const socket = useContext(WebSocketContext);

  const handleAdd = (userId: string) => {
    socket?.emit("addtofriends", {
      userId,
    });
    // I think better, if after add to channel stay popup in open state
    // onClose(); 
  };

  return (
    <div className="chat-popup-window">
      <h4 className="chat-popup-big-head">Members</h4>
      <div>
        {users.map((u) => (
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

interface ModalOverlayProps {
  onClose: () => void;
  children?: React.ReactNode;
}

function ModalOverlay({ onClose, children }: ModalOverlayProps) {
  return (
    <div className="chat-popup-overlay">
      <div>{children}</div>
    </div>
  );
}

function Friend() {
  const [showChannelMembers, setShowChannelMembers] = useState(false);
  const users = useContext(UsersContext);

  const columns = [
    { key: "username", name: "Username" },
    { key: "email", name: "Email" },
    { key: "status", name: "Status" },
    { key: "isFriend", name: "Is Friend" },
  ];
  const rows = users.map((user) => {
    return {
      username: user.username,
      email: user.email,
      status: user.status,
      isFriend: user.isFriend,
    };
  });

  const handleAddFriendClick = () => {
    setShowChannelMembers(true);
  };

  const handleClose = () => {
    setShowChannelMembers(false);
  };

  return (
    <>
      <Header />
      <Container>
        <Row className="zero-margin">
          <Col lg={12} xl={2} className="sidebar-global">
            <Sidebar />
          </Col>
          <Col lg={12} xl={10} className="container-fluid friends-margin-top">
            <Col xl={12}>
              <div className='inline '>
                <div className="left"><h1 className="heading heading-margin">Friends</h1></div>
                <div className="right">
                  <button className="AuthMargin heading-button" onClick={handleAddFriendClick}>
                    <img className="play-button-icon" src={PlusIcon} />
                    <div className="play-button-text">Add friend</div>
                  </button>
                </div>
              </div>
            </Col>

            {showChannelMembers && (
              <ModalOverlay onClose={handleClose}>
                <PopupAddFriends users={rows} onClose={handleClose} />
              </ModalOverlay>
            )}
            <div className="friends-area">
              <Tabs defaultActiveKey="all">
                <Tab
                  eventKey="all"
                  title={
                    <>
                      All users
                      <div className="mini-badge-friends">{users.length}</div>
                    </>
                  }
                  className="friends-table"
                >
                  <DataGrid
                    columns={columns}
                    rows={rows}
                    className="table-grid"
                  />
                </Tab>
                <Tab
                  eventKey="online"
                  title={
                    <>
                      Online
                      <div className="mini-badge-friends">{users.length}</div>
                    </>
                  }
                  className="friends-table"
                >
                  <DataGrid
                    columns={columns}
                    rows={rows}
                    className="table-grid"
                  />
                </Tab>
              </Tabs>
            </div>
          </Col>
        </Row>
      </Container>
    </>
  );
}

export default Friend;