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
      <div style={{ width: "90px" }}>
        <CircularProgressbarWithChildren
          value={100}
          strokeWidth={5}
          styles={buildStyles({
            pathColor: "#49C96D",
          })}
        >
          <img style={{ width: 40 }} src={Done} alt="Trophy" />
        </CircularProgressbarWithChildren>
      </div>
    );
  } else {
    return (
      <div style={{ width: "90px" }}>
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
      <Col xl={6} className="margin-card">
        <div className="card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements">Starting Strike</div>
            <div className="description-achievements">
              Win your first match in an online ping-pong game.
            </div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(user?.matchesWon, 1)}
            />
          </div>
        </div>
      </Col>
      <Col xl={6} className="margin-card">
        <div className="card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements">5 Wins</div>
            <div className="description-achievements">
              Win 5 games in an online ping-pong game in any mode.
            </div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(user?.matchesWon, 5)}
            />
          </div>
        </div>
      </Col>
      <Col xl={6} className="margin-card">
        <div className="card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements">10 Wins</div>
            <div className="description-achievements">
              Win 10 games in an online ping-pong game in any mode.
            </div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(user?.matchesWon, 10)}
            />
          </div>
        </div>
      </Col>
      <Col xl={6} className="margin-card">
        <div className="card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements">100 Wins</div>
            <div className="description-achievements">
              Win 100 games in an online ping-pong game in any mode.{" "}
            </div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(user?.matchesWon, 100)}
            />
          </div>
        </div>
      </Col>
      <Col xl={6} className="margin-card">
        <div className="card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements">Shy person</div>
            <div className="description-achievements">
              You have one friend, keep going!
            </div>
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
      <Col xl={6} className="margin-card">
        <div className="card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements">Band leader</div>
            <div className="description-achievements">
              You have five friends, nice!
            </div>
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
      <Col xl={6} className="margin-card">
        <div className="card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements">Football team leader</div>
            <div className="description-achievements">
              You have ten friends, fantastic!
            </div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(
                user?.friends.length,
                10
              )}
            />
          </div>
        </div>
      </Col>
      <Col xl={6} className="margin-card">
        <div className="card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements">Social beast</div>
            <div className="description-achievements">
              You have one hundred friends, amazing!
            </div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(
                user?.friends.length,
                100
              )}
            />
          </div>
        </div>
      </Col>
      <Col xl={6} className="margin-card">
        <div className="card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements">Baby punisher</div>
            <div className="description-achievements">
              You have one person banned.
            </div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(
                user?.blocked.length,
                1
              )}
            />
          </div>
        </div>
      </Col>
      <Col xl={6} className="margin-card">
        <div className="card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements">Angry</div>
            <div className="description-achievements">
              You have five people banned.
            </div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(
                user?.blocked.length,
                5
              )}
            />
          </div>
        </div>
      </Col>
      <Col xl={6} className="margin-card">
        <div className="card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements">Serial punisher</div>
            <div className="description-achievements">
              You have ten people banned.
            </div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(
                user?.blocked.length,
                10
              )}
            />
          </div>
        </div>
      </Col>
      <Col xl={6} className="margin-card">
        <div className="card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements">Dictactor</div>
            <div className="description-achievements">
              You have hundred people banned.
            </div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(
                user?.blocked.length,
                100
              )}
            />
          </div>
        </div>
      </Col>
      <Col xl={6} className="margin-card">
        <div className="card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements">Rookie</div>
            <div className="description-achievements">
              You have been online for five minutes !
            </div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(
                user?.logTimeInMinutes,
                5
              )}
            />
          </div>
        </div>
      </Col>
      <Col xl={6} className="margin-card">
        <div className="card-achievements inline inline-achievements auth-shadow">
          <div className="left width-text">
            <div className="heading-achievements">Master</div>
            <div className="description-achievements">
              Get a life. You have been online for one hour !
            </div>
          </div>
          <div className="right margin-circle">
            <CircularProgressBar
              percentage={percentageProgression(
                user?.logTimeInMinutes,
                60
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
