import React, { useContext } from 'react';
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


import Dropdown from 'react-bootstrap/Dropdown';
import { useAuth } from '../../Context/AuthContext';
import {UsersContext} from '../../Context/UsersContext';
import { HistoryMini } from '../History/HistoryMini';

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

function HeadingPage() {
  return (
    <Col xl={12}>
      <div className='inline '>
        <div className="left"><h1 className="heading heading-margin">Overview</h1></div>
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
  const count = nowCount <= maxCount ? nowCount : maxCount;
  return (
    <div className='rating-margin'>
      <div className='inline '>
        <div className="left">{parameter}</div>
        <div className="right">{count}/{maxCount}</div>
      </div>
      <div className='top-margin'>
        {ProgressLine(nowCount * 100 / maxCount, color)}
      </div>
    </div>
  )
}

function Widget1() {
  const {user} = useAuth();
  const users = useContext(UsersContext);
  const userConnected = users?.find(u => u.id === user?.id);
  return (
    <Col xl={4} className="margin-card">
      <div className='statistic-card auth-shadow'>
        <div className='inline '>
          <div className="left"><h2 className="heading-margin">Won matches</h2></div>
          {AlertInfo("Here you can see how many times you have won")}
        </div>
        {YourRating("Win first match", (userConnected?.matchesWon ?? 0), 1, "blue")}
        {YourRating("Win 5 times", (userConnected?.matchesWon ?? 0), 5, "orange")}
        {YourRating("Win 10 times", (userConnected?.matchesWon ?? 0), 10, "yellow")}
        {YourRating("Win 100 times", (userConnected?.matchesWon ?? 0), 100, "green")}
      </div>
    </Col>

  )
}


function Widget2({id}: {id: string}) {

  return (
    <Col xl={8} className="margin-card">
      <div className='statistic-card margin-card auth-shadow'>
        <h2 className='heading-all-games'>All Games</h2>
        <HistoryMini id={id}/>
      </div>
    </Col>
  )
}

function Body() {
  const {user} = useAuth();
  const users = useContext(UsersContext);
  const userConnected = users?.find(u => u.id === user?.id);
  return (
    <>
    { userConnected && (
  <Container>
    <Row className="zero-margin">
      <Col lg={12} xl={2} className='sidebar-global'>
        <Sidebar />
      </Col>
      <Col lg={12} xl={10}>
        <div className='content'>
          <Row>
            <HeadingPage />
            <Widget1 />
            <Widget2 id={userConnected.id} />
          </Row>
        </div>
      </Col>
    </Row>
  </Container>
)}
  </>)
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
