import _ from "lodash";
import { useContext, useEffect, useState } from "react";
import { Link, useLocation } from "react-router-dom";
import "./Sidebar.css";

import Dashboard from "./icons/Grid.svg";
import PlayIcon from "./icons/Cart.svg";
import CalendarIcon from "./icons/Calendar.svg";
import ChatIcon from "./icons/Chat.svg";
import FriendsIcon from "./icons/User.svg";
import AchievementsIcon from "./icons/Project.svg";
import SettingsIcon from "./icons/Settings.svg";
import HelpIcon from "./icons/Text.svg";
import Col from "react-bootstrap/Col";

import AvatarImg from "./../../Images/Avatar.jpg";
import PlayingImg from "./../../Images/playing.svg";
import { UnreadContext, UnreadStore } from "../../Context/UnreadContext";
import { UsersContext } from "../../Context/UsersContext";
import { UserStatus, User } from "../../Context/AuthContext";

function Avatar(avatar: string | undefined): any {
 return <img
    alt=""
    src={avatar ?? AvatarImg}
    width="40"
    height="40"
    className="d-inline-block align-top image-avatar-img"
    id="navbarScrollingDropdown"
  />
};

function Friend({ user }: {user: User}) {

  function statusCircle(isPlayNow: boolean) {
    if (isPlayNow) {
      return (
        <>
          <img alt="" src={PlayingImg} width="25" height="25" />
        </>
      );
    }
    return <></>;
  }

  function checkOnline(isOnline: boolean) {
    if (isOnline) {
      return (
        <>
          <div className="online-status-sidebar" />
        </>
      );
    }
  }

  return (
    <div
      className="friend-margin"
      style={{ cursor: "pointer" }}
    >
      <div className="flex-friend items-center">
        <Col lg={12} xl={3} className="padding-zero image-container">
          {Avatar(user.avatar)}
          {checkOnline(user.status === UserStatus.ONLINE)}
        </Col>
        <Col lg={12} xl={6} className="padding-zero friend-margin-center">
          <div className="friend-nickname">{user.username}</div>
          {/* <div className="friend-level">Level 1</div> */}
        </Col>
        <Col lg={12} xl={3} className="">
          {statusCircle(user.status === UserStatus.PLAYING)}
        </Col>
      </div>
    </div>
  );
}

const sidebarNavItems = [
  {
    display: "Dashboard",
    icon: (
      <img
        alt=""
        src={Dashboard}
        width="20"
        height="20"
        className="d-inline-block align-top sidebar-icon"
      />
    ),
    to: "/",
    section: "",
  },
  {
    display: "Start playing",
    icon: (
      <img
        alt=""
        src={PlayIcon}
        width="20"
        height="20"
        className="d-inline-block align-top sidebar-icon"
      />
    ),
    to: "/play",
    section: "play",
  },
  {
    display: "History",
    icon: (
      <img
        alt=""
        src={CalendarIcon}
        width="20"
        height="20"
        className="d-inline-block align-top sidebar-icon"
      />
    ),
    to: "/history",
    section: "history",
  },
  {
    display: "Chat",
    icon: (
      <img
        alt=""
        src={ChatIcon}
        width="20"
        height="20"
        className="d-inline-block align-top sidebar-icon"
      />
    ),
    to: "/chat",
    section: "chat",
  },
  {
    display: "Friends",
    icon: (
      <img
        alt=""
        src={FriendsIcon}
        width="20"
        height="20"
        className="d-inline-block align-top sidebar-icon"
      />
    ),
    to: "/friends",
    section: "friends",
  },
  {
    display: "Achievements",
    icon: (
      <img
        alt=""
        src={AchievementsIcon}
        width="20"
        height="20"
        className="d-inline-block align-top sidebar-icon"
      />
    ),
    to: "/achievements",
    section: "achievements",
  },
  {
    display: "Settings",
    icon: (
      <img
        alt=""
        src={SettingsIcon}
        width="20"
        height="20"
        className="d-inline-block align-top sidebar-icon"
      />
    ),
    to: "/settings",
    section: "settings",
  },
  {
    display: "Help",
    icon: (
      <img
        alt=""
        src={HelpIcon}
        width="20"
        height="20"
        className="d-inline-block align-top sidebar-icon"
      />
    ),
    to: "/help",
    section: "help",
  },
 
];

export function FullMenu() {
  const [activeIndex, setActiveIndex] = useState(0);
  const location = useLocation();
  const messsageCount = useContext<UnreadStore>(UnreadContext)?.unread || 0;

  // change active index
  useEffect(() => {
    const curPath = window.location.pathname.split("/")[1];
    const activeItem = sidebarNavItems.findIndex(
      (item) => item.section === curPath
    );
    setActiveIndex(curPath.length === 0 ? 0 : activeItem);
  }, [location]);

  return (
    <>
      <div className="sidebar__menu">
        {sidebarNavItems.map((item, index) => (
          <Link to={item.to} key={item.display}>
            <div
              className={`sidebar__menu__item ${
                activeIndex === index ? "active" : ""
              } ${index === 1 ? "play-button" : ""}`}
            >
              <div className="sidebar__menu__item__icon">{item.icon}</div>
              <div className="sidebar__menu__item__text">{item.display}</div>
              {messsageCount > 0 && item.display === "Chat" && (
                <div className="unread-messages-count">
                  {messsageCount > 9 ? "9+" : messsageCount}
                </div>
              )}
            </div>
          </Link>
        ))}
      </div>
    </>
  );
}

function Sidebar() {
  const users = useContext(UsersContext) ?? [];
  const friends = users.filter((u) => u.isFriend);
  return (
    <>
      <div className="sidebar">
        <FullMenu />
        <div className="friends-block">
          <div className="friends-heading">Your friends</div>
          {_(friends).sortBy("status").filter(f => !(f.hasBanned || f.isBanned)).reverse().map((user) => (
            <Friend key={user.id} user={user} />
          )).value()}
        </div>
      </div>
    </>
  );
}

export default Sidebar;
