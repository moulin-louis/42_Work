import React from 'react';
import './../../index.css';
import './Achievements.css';
import Header from '../../Navigation/Header/Header';
import Sidebar from '../../Navigation/Sidebar/Sidebar';

import Container from 'react-bootstrap/Container';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';

import { CircularProgressbar, CircularProgressbarWithChildren, buildStyles } from 'react-circular-progressbar';
import 'react-circular-progressbar/dist/styles.css';

import Done from './icons/trophy.svg';

// ________________ It's for parsing from userinfo ________________

const UserXp = 10
const UserGames = 9
const UserWins = 1 // 1 +
const UserWinsRow = 2 // 2 +

// I will have to write a formula for the calculation here, based on the saved data
// Bool
const UserWinElevenZero = 1 // 8
const UserWinElevenTen = 0 // 9
const UserRevenge = 1 // 19
// Not-Bool
const UserMaxSpeed = 98 // 12
const UserGlobalCheck = 2 // 14
const UserRatingCheck = 70 // 17, 20

//
const circleOne = UserWins > 0 ? 100 : 0;
const circleTwo = Math.round(UserWinsRow < 4 ? UserWinsRow / 3 * 100 : 100);

// ________________ It's for parsing from userinfo ________________

const dataArray = [
  {
    heading: "Starting Strike",
    description: "Win your first match in an online ping-pong game.",
    boost: 10,
    circle: circleOne
  },
  {
    heading: "Consistent Success",
    description: "Win three matches in a row.",
    boost: 20,
    circle: circleTwo
  },
  {
    heading: "Set Master",
    description: "Win a set with a score of 11-0.",
    boost: 40,
    circle: 10
  },
  {
    heading: "Duelist",
    description: "Win a match with a small difference in points (e.g., 11-10).",
    boost: 50,
    circle: 70
  },
  {
    heading: "Lightning Reaction",
    description: "Reach a ball flight speed of over 100 km/h.",
    boost: 60,
    circle: 20
  },
  {
    heading: "Global Player",
    description: "Play matches against players from 3 different campuses.",
    boost: 70,
    circle: 40
  },
  {
    heading: "Fearless",
    description: "Win a match against a player with 100XP more than you.",
    boost: 80,
    circle: 90
  },
  {
    heading: "Self-Affirmation",
    description: "Win against an opponent who previously defeated you.",
    boost: 90,
    circle: 80
  },
  {
    heading: "Online Ping-Pong Legend",
    description: "Achieve a Top-10 ranking among players and become an online ping-pong legend.",
    boost: 100,
    circle: 25
  },
  {
    heading: "5 Wins",
    description: "Win 5 games in an online ping-pong game in any mode.",
    boost: 110,
    circle: 55
  },
  {
    heading: "10 Wins",
    description: "Win 10 games in an online ping-pong game in any mode.",
    boost: 120,
    circle: 75
  },
  {
    heading: "100 Wins",
    description: "Win 100 games in an online ping-pong game in any mode.",
    boost: 130,
    circle: 95
  },
];


const CircularProgressBar = (input: {percentage:number}) => {
  if (input.percentage > 99) {
    return (
      <div style={{ width: "90px"}}>
        <CircularProgressbarWithChildren
          value={100}
          strokeWidth={5}
          styles={buildStyles({
              pathColor: '#49C96D',
          })}
          >
          <img
            style={{ width: 40}}
            src={Done}
            alt="Trophy"
          />
        </CircularProgressbarWithChildren>
      </div>
    )
  } else {
    return (
      <div style={{ width: "90px"}}>
          <CircularProgressbar
          value={input.percentage}
          strokeWidth={5}
          text={`${input.percentage}%`}
          styles={buildStyles({
            textSize: '18px',
            pathColor: `rgba(48, 79, 253, ${input.percentage / 100})`,
            textColor: '#3F434A',
            trailColor: '#F8F8F8',
            backgroundColor: '#3e98c7',
          })}
        />
      </div>
    );
  }
};

function HeadingPage() {
  return (
    <Col xl={12}>
      <div className='inline'>
        <div className="left"><h1 className="heading heading-margin">Achievements</h1></div>
      </div>
    </Col>

  )
}

function AllAchievements() {
  return (
    <>
      {dataArray.map((item) => (
        <Col xl={6} className="margin-card">
        <div className='card-achievements inline inline-achievements auth-shadow'>
          <div className='left width-text'>
            <div className="heading-achievements">
              {item.heading}
            </div>
            <div className="description-achievements">
              {item.description}
            </div>
          </div>
          <div className='margin-boost'>
            <div className="boost-achievements">
              ↑ {item.boost} XP
            </div>
          </div>
          <div className='right margin-circle'>
            <CircularProgressBar percentage={item.circle} />
          </div>
        </div>
      </Col>
      ))}
    </>
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
            <AllAchievements />
          </Row>
        </div>
      </Col>
    </Row>
  </Container>)
}

function Achievements() {
      return (
        <>
          <Header />
          <Body />
        </>
      );
    }

export default Achievements;
