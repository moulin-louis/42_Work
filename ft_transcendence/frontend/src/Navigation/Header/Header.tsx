import { Outlet } from "react-router-dom";
import "./Header.css";
import { FullMenu } from "../Sidebar/Sidebar";
import Container from "react-bootstrap/Container";
import NavDropdown from "react-bootstrap/NavDropdown";
import Nav from "react-bootstrap/Nav";
import Navbar from "react-bootstrap/Navbar";
import NotifyImg from "./../../Images/Notify.svg";
import NotifyEmptyImg from "./../../Images/NotifyEmpty.svg";
import Logo from "./../../Images/Logo.svg";
import { useContext, useEffect, useState } from "react";
import LeaveIcon from "./../../Images/Leave.svg";
import SettingsIcon from "./../../Images/Settings.svg";
import UserIcon from "./../../Images/User.svg";
import MailIcon from "./../../Images/Mail.svg";
import TasksIcon from "./../../Images/Tasks.svg";
import { UnreadContext, UnreadStore } from "../../Context/UnreadContext";
import Dropdown from "react-bootstrap/Dropdown";
import { useAuth } from "../../Context/AuthContext";
import { Socket } from "socket.io-client";
import { WebSocketContext } from "../../Context/WebSocketContext";

function CheckNotify(state: number) {
  if (state > 0) {
    return NotifyImg;
  }
  return NotifyEmptyImg;
}

function NotifyButton() {
  const messsageCount = useContext<UnreadStore>(UnreadContext)?.unread || 0;

  return (
    <>
      <Dropdown className="menu-toogle">
        <Dropdown.Toggle variant="" id="dropdown-basic">
          <img
            alt=""
            src={CheckNotify(messsageCount)}
            width="22"
            height="22"
            className="d-inline-block align-top"
          />
        </Dropdown.Toggle>

        <Dropdown.Menu className="chat-dropdown-style">
          <div className="dropdown-count-notify">
            <div className="notify-header">
              <b>Notifications</b>
            </div>
            {messsageCount > 0 && (
              <div className="unread-messages-count">
                {messsageCount > 9 ? "9+" : messsageCount}
              </div>
            )}
          </div>
          <NavDropdown.Divider />
          {messsageCount == 0 &&
            (<Dropdown.Item className="dropdown-notify-empty">
              <div className="vertical-align mobile-vertical notify-card-drop">
                <div className="notify-empty-header-text">
                  <div className="notify-empty-head">
                    <b>No notifications yet</b>
                  </div>
                  Start being social for them to show up
                </div>
              </div>
            </Dropdown.Item>)
          }
          {messsageCount > 0 &&
            (<Dropdown.Item className="dropdown-notify-empty">
              <div className="vertical-align mobile-vertical notify-card-drop">
                <div className="notify-empty-header-text">
                  <div className="notify-empty-head">
                    <b>{messsageCount} notification(s)</b>
                  </div>
                  I will wait backend for that part
                </div>
              </div>
            </Dropdown.Item>)
          }
        </Dropdown.Menu>
      </Dropdown>
    </>
  );
}

function UserProfile() {
  const { user } = useAuth();
  const messsageCount = useContext<UnreadStore>(UnreadContext)?.unread ?? 0;
  const socket = useContext<Socket | undefined>(WebSocketContext);


  const { logout, accessToken } = useAuth();
  const token = accessToken;

  const handleLogout = async () => {
    console.log('Logging out...');
    await logout();
    window.location.href = 'http://localhost:4000/auth' //TODO mettre dans le .env process.env
  };


  return (
    <>
      <div className="big-menu">
        <NotifyButton />
      </div>
      <div className="separator-header"></div>
      <NavDropdown
        title={
          <div className="vertical-align mobile-vertical">
            <img
              alt=""
              src={user?.avatar}
              className="avatar-header sidebar-icon dropdown-icon-button"
            />
            <div className="username-header-text">{user?.username}</div>
          </div>
        }
        id="navbarScrollingDropdown"
        className="dropdown-user vertical-align dropdown-shadow"
      >
        <div className="area-drop-avatar vertical-align mobile-vertical user-card-drop">
          <img
            alt=""
            src={user?.avatar}
            width="20"
            height="20"
            className="avatar-header sidebar-icon dropdown-icon-button"
          />
          <div className="username-header-text">
            <b>{user?.username}</b>
            <br></br>
            Nickname 42
          </div>
        </div>
        <NavDropdown.Divider />
        <NavDropdown.Item className="chat-drop-menu-item" href="/profile">
          <div className="box-with-icon">
            <div>
              <img
                alt=""
                src={UserIcon}
                width="20"
                height="20"
                className="sidebar-icon dropdown-icon-button"
              />
            </div>
            <div className="dropdown-name-button">My Profile</div>
          </div>
        </NavDropdown.Item>
        <NavDropdown.Item className="chat-drop-menu-item" href="/chat">
          <div className="box-with-icon">
            <div>
              <img
                alt=""
                src={MailIcon}
                width="20"
                height="20"
                className="sidebar-icon dropdown-icon-button"
              />
            </div>
            <div className="dropdown-name-button">
              My messages
              {/* {messsageCount > 0 && (
                <div className="unread-messages-count">
                  {messsageCount > 9 ? "9+" : messsageCount}
                </div>
              )} */}
            </div>
          </div>
        </NavDropdown.Item>
        <NavDropdown.Item className="chat-drop-menu-item" href="/friends">
          <div className="box-with-icon">
            <div>
              <img
                alt=""
                src={UserIcon}
                width="20"
                height="20"
                className="sidebar-icon dropdown-icon-button"
              />
            </div>
            <div className="dropdown-name-button">My Friends</div>
          </div>
        </NavDropdown.Item>
        <NavDropdown.Divider />
        <NavDropdown.Item className="chat-drop-menu-item" href="/settings">
          <div className="box-with-icon">
            <div>
              <img
                alt=""
                src={SettingsIcon}
                width="20"
                height="20"
                className="sidebar-icon dropdown-icon-button"
              />
            </div>
            <div className="dropdown-name-button">Settings</div>
          </div>
        </NavDropdown.Item>
        <NavDropdown.Item className="chat-drop-menu-item" href="/blacklist">
          <div className="box-with-icon">
            <div>
              <img
                alt=""
                src={TasksIcon}
                width="20"
                height="20"
                className="sidebar-icon dropdown-icon-button"
              />
            </div>
            <div className="dropdown-name-button">Blacklist</div>
          </div>
        </NavDropdown.Item>
        <NavDropdown.Divider />
        <NavDropdown.Item className="chat-drop-menu-item" onClick={handleLogout}>
          <div className="box-with-icon">
            <div>
              <img
                alt=""
                src={LeaveIcon}
                width="20"
                height="20"
                className="sidebar-icon dropdown-icon-button"
              />
            </div>
            <div className="dropdown-name-button">Leave</div>
          </div>
        </NavDropdown.Item>
      </NavDropdown>
    </>
  );
}

function Header() {
  return (
    <>
      <Navbar bg="white" expand="xl">
        <Container fluid>
          <Navbar.Brand href="/">
            <img className="auth-logo-center" src={Logo} alt="Logo" />
          </Navbar.Brand>
          <div className="mobile-menu">
            <UserProfile />
          </div>
          <Navbar.Toggle aria-controls="navbarScroll" />
          <Navbar.Collapse id="navbarScroll">
            <Nav
              className="me-auto my-2 my-lg-0"
              style={{ maxHeight: "100px" }}
              navbarScroll
            ></Nav>
            <div className="big-menu">
              <UserProfile />
            </div>
            <div className="mobile-menu">
              <FullMenu />
            </div>
          </Navbar.Collapse>
        </Container>
      </Navbar>
      <div id="detail1">
        <Outlet />
      </div>
    </>
  );
}

export default Header;
