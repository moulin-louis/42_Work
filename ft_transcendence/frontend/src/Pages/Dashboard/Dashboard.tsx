import React from 'react';
import './../../index.css';
import './Dashboard.css';
import Header from './../../Navigation/Header/Header';
import Sidebar from './../../Navigation/Sidebar/Sidebar';

import Container from 'react-bootstrap/Container';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';
import ProgressBar from 'react-bootstrap/ProgressBar';

import OverlayTrigger from 'react-bootstrap/OverlayTrigger';
import Tooltip from 'react-bootstrap/Tooltip';
import AlertIcon from './../../Images/Alert.svg';

import FriendIMG from "./../../Images/Avatar.jpg";

import Dropdown from 'react-bootstrap/Dropdown';

function AlertInfo(alertMessage : string) {
  return (
    <>
      <OverlayTrigger
        key={'left'}
        placement={'left'}
        overlay={
          <Tooltip id={`tooltip-${'left'}`}>
            {alertMessage}
          </Tooltip>
        }
      >
        <div className="right"><img
          alt=""
          src={AlertIcon}
          width="20"
          height="20"
          className="alert-icon-margin"
          id="navbarScrollingDropdown"
        /></div>
      </OverlayTrigger>
    </>
  );
}

function SortButton() {
  return (
    <Dropdown>
      <Dropdown.Toggle variant="success" id="dropdown-basic" className="sort-button">
        Last 7 Days
      </Dropdown.Toggle>

      <Dropdown.Menu>
        <Dropdown.Item href="#/action-1">Last 3 Days</Dropdown.Item>
        <Dropdown.Item href="#/action-2">Last 7 Days</Dropdown.Item>
        <Dropdown.Item href="#/action-3">Last 30 Days</Dropdown.Item>
      </Dropdown.Menu>
    </Dropdown>
  )
}

function HeadingPage() {
  return (
    <Col xl={12}>
      <div className='inline '>
        <div className="left"><h1 className="heading heading-margin">Overview</h1></div>
        <div className="right">
          <SortButton />
        </div>
      </div>
    </Col>

  )
}

function ProgressLine(now: number, color: string) {
  return <ProgressBar
    now={now}
    label={`${now}%`}
    visuallyHidden
    className={color}
  />;
}

function YourRating(parameter: string, nowCount: number, maxCount: number, color: string) {
  return (
    <div className='rating-margin'>
      <div className='inline '>
        <div className="left">{parameter}</div>
        <div className="right">{nowCount}/{maxCount}</div>
      </div>
      <div className='top-margin'>
        {ProgressLine(nowCount * 100 / maxCount, color)}
      </div>
    </div>
  )
}

function Widget1() {
  return (
    <Col xl={4} className="margin-card">
      <div className='statistic-card auth-shadow'>
        <div className='inline '>
          <div className="left"><h2 className="heading-margin">Achievements</h2></div>
          {AlertInfo("It's text about achievements")}
        </div>
        {YourRating("Check", 1, 1, "blue")}
        {YourRating("Win 5 times", 4, 5, "orange")}
        {YourRating("Win 10 times", 3, 10, "yellow")}
        {YourRating("Win 100 times", 27, 100, "green")}
      </div>
    </Col>

  )
}

// Avatar of user
const avatarUsername = <img
  alt=""
  src={FriendIMG}
  width="40"
  height="40"
  className="d-inline-block align-top avatar-img"
  id="navbarScrollingDropdown"
/>

function FriendBoard() {
    return (
        <div className='friend-margin'>
                <div className="flex-friend items-center">
                    <Col lg={12} xl={3} className='padding-zero'>
                        {avatarUsername}
                    </Col>
                    <Col lg={12} xl={6} className='padding-zero'>
                        <div className='friend-nickname'>Ealease</div>
                        <div className='friend-level'>Level 1</div>
                    </Col>
                    <Col lg={12} xl={3} className=''>
                        O
                    </Col>
                </div>
            </div>
    )
}

function Widget2() {
  return (
    <Col xl={5} className="margin-card">
      <div className='statistic-card auth-shadow'>
        <h2>Latest Games</h2>
        <div className=''>
            {/* <FriendBoard />
            <FriendBoard />
            <FriendBoard />
            <FriendBoard />
            <FriendBoard /> */}
        </div>
      </div>
    </Col>

  )
}

function Widget3() {
  return (
    <Col xl={3} className="margin-card">
      <div className='statistic-card margin-card auth-shadow'>
        <h2>All Games</h2>
      </div>

      <div className='statistic-card auth-shadow'>
        <h2>Your Level</h2>
      </div>
    </Col>
  )
}

function Body() {
  return (<Container>
    <Row className="zero-margin">
      <Col lg={12} xl={2} className='sidebar-global'>
        <Sidebar />
      </Col>
      <Col lg={12} xl={10}>
        <div className='content'>
          <Row>
            <HeadingPage />
            <Widget1 />
            <Widget2 />
            <Widget3 />
          </Row>
        </div>
      </Col>
    </Row>
  </Container>)
}

function Dashboard() {
  return (
    <>
      <Header />
      <Body />
    </>
  );
}

export default Dashboard;
