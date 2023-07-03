import React, { useContext } from "react";
import "./../../index.css";
import "./Achievements.css";
import Header from "../../Navigation/Header/Header";
import Sidebar from "../../Navigation/Sidebar/Sidebar";

import Container from "react-bootstrap/Container";
import Row from "react-bootstrap/Row";
import Col from "react-bootstrap/Col";

import {
  CircularProgressbar,
  CircularProgressbarWithChildren,
  buildStyles,
} from "react-circular-progressbar";
import "react-circular-progressbar/dist/styles.css";

import Done from "./icons/trophy.svg";
import { useAuth } from "../../Context/AuthContext";
import { UsersContext } from "../../Context/UsersContext";

const CircularProgressBar = (input: { percentage: number }) => {
  if (input.percentage > 99) {
    return (
      <div style={{ width: "50px" }}>
        <CircularProgressbarWithChildren
          value={100}
          strokeWidth={5}
          styles={buildStyles({
            pathColor: "#49C96D",
          })}
        >
          <img style={{ width: 20 }} src={Done} alt="Trophy" />
        </CircularProgressbarWithChildren>
      </div>
    );
  } else {
    return (
      <div style={{ width: "50px" }}>
        <CircularProgressbar
          value={input.percentage}
          strokeWidth={5}
          text={`${input.percentage}%`}
          styles={buildStyles({
            textSize: "18px",
            pathColor: `rgba(48, 79, 253, ${input.percentage / 100})`,
            textColor: "#3F434A",
            trailColor: "#F8F8F8",
            backgroundColor: "#3e98c7",
          })}
        />
      </div>
    );
  }
};

function HeadingPage() {
  return (
    <Col xl={12}>
      <div className="inline">
        <div className="left">
          <h1 className="heading heading-margin">Achievements</h1>
        </div>
      </div>
    </Col>
  );
}

function percentageProgression(progression: number | undefined, total: number) {
  return Math.trunc(100 * (progression ?? 0) / total);
}

export function AchievementsMini({user}: {user: any}) {
  return (
    <>
      <Col xl={4} className="margin-card">
        <div className="small-card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements-small">Starting Strike</div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(user?.matchesWon, 1)}
            />
          </div>
        </div>
      </Col>
      <Col xl={4} className="margin-card">
        <div className="small-card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements-small">5 Wins</div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(user?.matchesWon, 5)}
            />
          </div>
        </div>
      </Col>
      <Col xl={4} className="margin-card">
        <div className="small-card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements-small">10 Wins</div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(user?.matchesWon, 10)}
            />
          </div>
        </div>
      </Col>
      <Col xl={4} className="margin-card">
        <div className="small-card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements-small">100 Wins</div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(user?.matchesWon, 100)}
            />
          </div>
        </div>
      </Col>
      <Col xl={4} className="margin-card">
        <div className="small-card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements-small">Shy person</div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(
                user?.friends.length,
                1
              )}
            />
          </div>
        </div>
      </Col>
      <Col xl={4} className="margin-card">
        <div className="small-card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements-small">Band leader</div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(
                user?.friends.length,
                5
              )}
            />
          </div>
        </div>
      </Col>
    </>
  );
}

function Body() {
  const { user } = useAuth();
  const users = useContext(UsersContext);
  const userConnected = users?.find((u) => u.id === user?.id);
  return (
    <Container>
      { userConnected && (
      <Row className="zero-margin">
        <Col lg={12} xl={2} className="sidebar-global">
          <Sidebar />
        </Col>
        <Col lg={12} xl={10}>
          <div className="content">
            <Row>
              <HeadingPage />
              <AchievementsMini user={userConnected}/>
            </Row>
          </div>
        </Col>
      </Row>
  )}
    </Container>
  );
}

function AchievementsMin() {
  return (
    <>
      <Header />
      <Body />
    </>
  );
}

export default AchievementsMin;
