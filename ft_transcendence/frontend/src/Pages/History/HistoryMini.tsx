import Header from "../../Navigation/Header/Header";
import Container from "react-bootstrap/Container";
import Sidebar from "../../Navigation/Sidebar/Sidebar";
import Row from "react-bootstrap/Row";
import Col from "react-bootstrap/Col";
import { WebSocketContext } from "../../Context/WebSocketContext";
import { useContext, useEffect, useState } from "react";
import './History.css';
import QuanityIcon from "./../Game/icons/Quanity.svg"
import UpIcon from "./../Game/icons/Up.svg"
import RetroIcon from "./../Game/icons/Retro.svg"
import Tabs from 'react-bootstrap/Tabs';
import Tab from 'react-bootstrap/Tab';
import moment from 'moment';
import { useAuth } from "../../Context/AuthContext";
import {UsersContext} from "../../Context/UsersContext";

function GameType() {
  return (
    <>
      <div className="game-type-box-history">
        <img
          style={{ width: 40, marginRight: 15 }}
          src={QuanityIcon}
          alt="Quanity"
        />
        <img
          style={{ width: 40, marginRight: 15 }}
          src={UpIcon}
          alt="Quanity"
        />
        <img
          style={{ width: 40, marginRight: 15 }}
          src={RetroIcon}
          alt="Quanity"
        />
      </div>
    </>
  )
}

function HeadingPage() {
  return (
    <Col xl={12}>
      <h1 className="heading heading-margin-history">History of your games</h1>
    </Col>

  )
}

interface IMatchInfo {
  id: string,
  winner: string,
  loser: string,
  draw: boolean,
  winnerScore: number,
  loserScore: number,
  createdAt: Date,
}

const WinnerInfo = ({ match_info }: any) => {
  return (
    <>
      <div className="game-inline-card">
        <Col lg={12} xl={12} className="padding-zero">
          <img
            alt=""
            src={match_info.winner?.avatar}
            className="game-auto-margin game-avatar-mini game-avatar-empty"
          />
          <div className="game-nickname-card">{match_info.winner}</div>
        </Col>
      </div>
    </>
  );
}

const LoserInfo = ({ match_info }: any) => {
  return (
    <>
      <div className="game-inline-card">
        <Col lg={12} xl={12} className="padding-zero">
          <img
            alt=""
            src={match_info.loser?.avatar}
            className="game-auto-margin game-avatar-mini game-avatar-empty"
          />
          <div className="game-nickname-card">{match_info.loser}</div>
        </Col>
      </div>
    </>
  );
}

const MatchHistory = ({ match_info }: any) => {
  return (
    <div>
      <div className="time-badge">{moment(match_info.createdAt).fromNow()}</div>
      <div className="history-inline-card">
        <Col sm={3}>
          <WinnerInfo match_info={match_info} />
        </Col>
        <Col sm={6}>
          <div className="history-score score-margin">{match_info.winnerScore} : {match_info.loserScore}</div>
          {match_info.draw ? <div className="score-margin">Draw</div>: <div></div>}
        </Col>
        <Col sm={3}>
          <LoserInfo match_info={match_info} />
        </Col>
      </div>
      <div>
        <GameType />
      </div>
    </div>
  );
}

const useGameHistory = (id: string) => {
  const socket = useContext(WebSocketContext);
  const [match_won, setMatchWon] = useState<IMatchInfo[]>([]);
  const [match_lost, setMatchLost] = useState<IMatchInfo[]>([]);
  const [match_draw, setMatchDraw] = useState<IMatchInfo[]>([]);

  useEffect(() => {
    socket?.emit("get_win_history_id", id);
    socket?.emit("get_lost_history_id", id);
    socket?.emit("get_draw_history_id", id);
    socket?.on("get_win_history_id", (payload: IMatchInfo[]) => setMatchWon(payload));
    socket?.on("get_lost_history_id", (payload: IMatchInfo[]) => setMatchLost(payload));
    socket?.on("get_draw_history_id", (payload: IMatchInfo[]) => {setMatchDraw(payload)});
    return () => {
      socket?.off("get_win_history_id");
      socket?.off("get_lost_history_id");
      socket?.off("get_draw_history_id");
    }
  }, [socket, id]);

  return { match_won, match_lost, match_draw };
}

const UserDrawHistory = ({ match_draw }: any) => {
  return (
    <div className='row'>
      {
        match_draw.length === 0 ?
          (<h1>No draw match</h1>) :
          (match_draw.map((match_info: IMatchInfo) => (
            <>
              <Col key={match_info.id} xl={6} className="margin-card">
                <div className='history-card auth-shadow'>
                  <div className='inline '>
                    <MatchHistory match_info={match_info} />
                  </div>
                </div>
              </Col>
            </>)
          ))
      }
    </div>
  );
}

const UserWonHistory = ({ match_won }: any) => {
  return (
    <div className='row'>
      {
        match_won.length === 0 ?
          (<h1>No match won</h1>) :
          (match_won.map((match_info: IMatchInfo) => (
            <>
              <Col key={match_info.id} xl={6} className="margin-card">
                <div className='history-card auth-shadow'>
                  <div className='inline '>
                    <MatchHistory match_info={match_info} />
                  </div>
                </div>
              </Col>
            </>)
          ))
      }
    </div>
  );
}

const UserLostHistory = ({ match_lost }: any) => {
  return (
    <div className='row'>
      {
        match_lost.length === 0 ?
          (<h1>No match lost</h1>) :
          (match_lost.map((match_info: IMatchInfo) => (
            <>
              <Col key={match_info.id} xl={6} className="margin-card">
                <div className='history-card auth-shadow'>
                  <div className='inline '>
                    <MatchHistory match_info={match_info} />
                  </div>
                </div>
              </Col>
            </>)
          ))
      }
    </div>
  );
}

const UserAllHistory = ({ match_won, match_lost, match_draw }: any) => {
  let allGames: IMatchInfo[] = [...match_won, ...match_lost, ...match_draw];
  return (
      <>
        <div className='row'>
          {
            allGames.length === 0 ?
              (<h1>No games played</h1>) :
              (allGames.map((match_info: IMatchInfo) => (
                <Col key={match_info.id} xl={6} className="margin-card">
                  <div className='history-card auth-shadow'>
                    <div className='inline '>
                      <MatchHistory match_info={match_info} />
                    </div>
                  </div>
                </Col>
              )))
          }
        </div>
      </>
    );
}

export function HistoryMini({id}: {id: string}) {
  const { match_won, match_lost, match_draw } = useGameHistory(id);
  const totalGames = match_won.length + match_lost.length + match_draw.length;
  return (
    <>
      <Col xl={12}>
        <div className="help-page">
          <Tabs>
            <Tab eventKey="All"
              title={
                <>
                  All
                  <div className="mini-badge-friends">{totalGames}</div>
                </>
              }
              className="friends-table"
            >
              <UserAllHistory match_won={match_won} match_lost={match_lost} match_draw={match_draw}/>
            </Tab>
            <Tab eventKey="Winning"
              title={
                <>
                  Winning
                  <div className="mini-badge-friends">{match_won.length}</div>
                </>
              }
              className="friends-table"
            >
              <UserWonHistory match_won={match_won} />
            </Tab>
            <Tab eventKey="Losing"
              title={
                <>
                  Losing
                  <div className="mini-badge-friends">{match_lost.length}</div>
                </>
              }
              className="friends-table"
            >
              <UserLostHistory match_lost={match_lost} />
            </Tab>
            <Tab eventKey="Draw"
                 title={
                   <>
                     Draw
                     <div className="mini-badge-friends">{match_draw.length}</div>
                   </>
                 }
                 className="friends-table"
            >
              <UserDrawHistory match_draw={match_draw} />
            </Tab>
          </Tabs>
        </div>
      </Col>
    </>
  );
}


export const BodyHistory = () => {
  const {user} = useAuth();
  const users = useContext(UsersContext);
  const userConnected = users?.find(u => u.id === user?.id);
  return (
    <>
    {userConnected && (
    <Container>
      <Row className="zero-margin">
        <Col lg={12} xl={2} className="sidebar-global">
          <Sidebar />
        </Col>
        <Col lg={12} xl={10}>
          <div className="content">
            <Row>
              <HeadingPage />
              <HistoryMini id={userConnected.id}  />
            </Row>
          </div>
        </Col>
      </Row>
    </Container>
    
  )}
  </>
  );
};


const HistoryMin = () => {
  return (
    <>
      <Header />
      <BodyHistory/>
    </>
  );
}

export default HistoryMin;
