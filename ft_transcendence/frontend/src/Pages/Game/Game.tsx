import React, { useState, useEffect, useContext, useRef } from "react";
import Row from "react-bootstrap/Row";
import Col from "react-bootstrap/Col";
import { useLocation } from "react-router-dom";
import { Socket } from "socket.io-client";
import { WebSocketContext } from "../../Context/WebSocketContext";
import Header from "./../../Navigation/Header/Header";
import Sidebar from "./../../Navigation/Sidebar/Sidebar";
import Container from "react-bootstrap/Container";
import "./Game.css";
import PlayIcon from "./../../Navigation/Sidebar/icons/Cart.svg";
import PlusIcon from "./icons/PlusBlue.svg";
import NewGameCard from "./GameCard";
import PopupNewGame from "./GamePopup"

interface IPosition {
  x: number;
  y: number;
}

enum GameState {
  WIN,
  LOSE,
}
// this function is used to handle socket events
const useSocketEvent = (socket: Socket | undefined, event: string, handler: any): void => {
  useEffect(() => {
    socket?.on(event, handler);
    return (): void => {
      socket?.off(event);
    };
  }, [socket, event, handler]);
}

// This code creates a paddle that is updated when the server sends a new position.
const usePaddle: any = (eventKey: any, color: string, className: string, width_div: number, height_div: number) => {
  const socket = useContext(WebSocketContext);
  const scale_x: number = width_div / 1552;
  const scale_y: number = height_div / 400;
  const [position, setPosition] = useState<IPosition>({ x: 0, y: 0 });
  useSocketEvent(socket, eventKey, (payload: IPosition): void => {
    setPosition({ x: payload.x * scale_x, y: payload.y * scale_y });
  });
  const style = {
    position: "absolute",
    left: position.x,
    top: position.y,
    backgroundColor: color,
  };
  return { className, tabIndex: 0, style };
}

// This code creates a player bar that can be controlled with the w and s keys.
// It uses the WebSocketContext to handle communication with the server.
// The player's position is stored in the state variable "position".
// The "position" variable is updated when the "Player_Position" event is received.
// The "Move" event is emitted when the player press w or s keys
const PlayerBar = ({ width_div, height_div }: { width_div: number, height_div: number }) => {
  const paddleProps = usePaddle("Player_Position", "green", "paddle left", width_div, height_div);
  const socket = useContext(WebSocketContext);
  const keysRef = useRef(new Set());
  useEffect(() => {
    const handleKeyDown = (event: any): void => {
      keysRef.current.add(event.key);
    };
    const handleKeyUp = (event: any): void => {
      keysRef.current.delete(event.key);
    };
    document.body.addEventListener('keydown', handleKeyDown);
    document.body.addEventListener('keyup', handleKeyUp);
    return (): void => {
      document.body.removeEventListener('keydown', handleKeyDown);
      document.body.removeEventListener('keyup', handleKeyUp);
    };
  }, []);
  useEffect(() => {
    const intervalId: NodeJS.Timer = setInterval((): void => {
      if (keysRef.current.has('ArrowUp')) socket?.emit('Move', 'ArrowUp');
      if (keysRef.current.has('ArrowDown')) socket?.emit('Move', 'ArrowDown');
    }, 30);  // adjust interval as needed

    return () => clearInterval(intervalId);
  }, [socket]);
  return (
    <div {...paddleProps}></div>
  );
};


// This code gets the position of the enemy paddle from the server and sets it to the correct position
const EnemyBar = ({ width_div, height_div }: { width_div: number, height_div: number }) => {
  const paddleProps = usePaddle("EnemyPos", "red", "paddle right", width_div, height_div);
  return (
    <div {...paddleProps}></div>
  );
};

// This code gets the score of the player from the server and sets it to the correct score
const PlayerScore = () => {
  const socket = useContext(WebSocketContext);
  const [score, setScore] = useState<number>(0);

  useSocketEvent(socket, "PlayerScore", (payload: number) => setScore(payload));
  return <div className="score score-left">{score}</div>;
};

// This code gets the score of the enemy from the server and sets it to the correct score
const EnemyScore = () => {
  const socket = useContext(WebSocketContext);
  const [score, setScore] = useState<number>(0);

  useSocketEvent(socket, "EnemyScore", (payload: number) => setScore(payload));
  return <div className="score score-right">{score}</div>;
};

// This code gets the position of the ball from the server and sets it to the correct position
const Ball = ({ width_div, height_div }: { width_div: number, height_div: number }) => {
  const socket = useContext(WebSocketContext);
  const [position, setPosition] = useState<IPosition>({ x: 180, y: 300 });
  const scale_x: number = width_div / 1552;
  const scale_y: number = height_div / 400;
  useSocketEvent(socket, "GetPositionBall", (payload: IPosition) => setPosition({ x: payload.x * scale_x, y: payload.y * scale_y }));
  return (
    <svg height={400} width={1552}>
      <circle cx={position.x} cy={position.y} r="10" fill="white" />
    </svg>
  );
};

const GameOver = ({ status, handleGameOver }: any) => {
  const close_game = (): void => {
    handleGameOver(false);
  }
  return (
    <div className="game-over-back">
      <div className="game-over">
        {status === GameState.WIN ? (<h1 className="game-over-head heading-margin">🎉 You win!</h1>) : (<h1 className="game-over-head heading-margin">😵 You lose!</h1>)}
        <button onClick={close_game}
          className="AuthMargin heading-button">
          <div className="play-button-text">
            Back to the games page
          </div>
        </button>
      </div>
    </div>
  )
}

// This code creates the game board
export const PongGame = ({ handleGameOver }: any) => {
  const [game_state, setGameState] = useState<GameState | null>(null);
  const [game_ended, setGameEnded] = useState<boolean>(false);
  const socket = useContext(WebSocketContext);

  useSocketEvent(socket, "GameOver", (payload: { winner: string }): void => {
    if (payload.winner === 'you') {
      setGameEnded(true);
      setGameState(GameState.WIN);
    } else if (payload.winner === 'not_you') {
      setGameEnded(true);
      setGameState(GameState.LOSE);
    }
  });

  const divRef = useRef<HTMLDivElement>(null);
  const [width_div, setWidthDiv] = useState<number>(0);
  const [height_div, setHeightDiv] = useState<number>(0);
  useEffect(() => {
    const handleResize = (): void => {
      const { current }: { current: HTMLDivElement | null } = divRef;
      if (current) {
        const { width, height }: { width: number, height: number } = current.getBoundingClientRect();
        setHeightDiv(height);
        setWidthDiv(width);
      }
    }
    handleResize();
    window.addEventListener('resize', handleResize);
    return () => window.removeEventListener('resize', handleResize);
  }, [divRef]);
  return (
    <div className="game-board" ref={divRef}>
      {
        game_ended ? <GameOver status={game_state} handleGameOver={handleGameOver} />
          : (<div>
            <PlayerBar width_div={width_div} height_div={height_div} />
            <EnemyBar width_div={width_div} height_div={height_div} />
            <PlayerScore />
            <EnemyScore />
            <SeparatorLine />
            <Ball width_div={width_div} height_div={height_div} />
          </div>)
      }
    </div>
  );
};

// This code creates the game lobby, waiting in matchmaking room for a player
const Lobby = ({ changeWaitingGame, handle_GO }: any) => {
  const socket = useContext(WebSocketContext);
  useSocketEvent(socket, "matchmaking", (payload: boolean): void => { if (payload) changeWaitingGame(false); });
  return (
    <Row>
      <NewGameCard status="waiting" handleClose={handle_GO} />
      {/* <NewGameCard status="disabled" /> */}
      {/* <NewGameCard status="default" /> */}
    </Row>
  );
};

// This function is used to handle the game state of the user.
// It is used to start the matchmaking process, and to handle when the game is over.
// It also handles the waiting state of the user, when the user is waiting for an opponent.
export const useGameState = () => {
  const [LaunchGame, setLaunchGame] = useState(false);
  const [waitingGame, setWaitingGame] = useState<boolean>(true);
  const socket = useContext(WebSocketContext);
  const handleGameOver = (): void => {
    setLaunchGame(false);
    setWaitingGame(true);
  }
  useEffect(() => {
    const handleMatchmaking = (payload: boolean): void => {
      if (payload) setWaitingGame(false);
    }
    socket?.on("GameOver", handleGameOver);
    socket?.on("matchmaking", handleMatchmaking);
    return () => {
      socket?.off("GameOver", handleGameOver);
      socket?.off("matchmaking", handleMatchmaking);
    }
  }, [socket]);
  const startMatchmaking = (mode: any): void => {
    socket?.emit("matchmaking", mode);
    setLaunchGame(true);
  }
  return { LaunchGame, waitingGame, startMatchmaking, setWaitingGame, handleGameOver, setLaunchGame };
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

function SeparatorLine() {
  return (
    <div className="line-div">
      <div className="line-pp"></div>
    </div>
  )
}

const Body = () => {
  const { LaunchGame, waitingGame, startMatchmaking, setWaitingGame, handleGameOver, setLaunchGame } = useGameState();
  const [showChannelMembers, setShowChannelMembers] = useState(false);
  const location = useLocation();
  useEffect((): void => {
    if (location?.state) {
      setWaitingGame(false);
      setLaunchGame(true);
    }
  }, [setWaitingGame, setLaunchGame, location]);
  const handleAddFriendClick = (): void => {
    setShowChannelMembers(true);
  };

  const handleClose = (): void => {
    setShowChannelMembers(false);
  };

  return (
    <Container>
      <Row className="zero-margin">
        <Col lg={12} xl={2} className="sidebar-global">
          <Sidebar />
        </Col>
        <Col lg={12} xl={10}>
          <div className="content">
            <Col xl={12}>
              <div className='inline '>
                <div className="left"><h1 className="heading heading-margin">Waiting list</h1></div>
                <div className="right">
                  <button className="AuthMargin heading-button" onClick={handleAddFriendClick}>
                    <img className="play-button-icon" src={PlayIcon} alt="" />
                    <div className="play-button-text">New game</div>
                  </button>
                </div>
              </div>
            </Col>
            {showChannelMembers && (
              <ModalOverlay onClose={handleClose}>
                <PopupNewGame onClose={handleClose} startMatchmaking={startMatchmaking} />
              </ModalOverlay>
            )}
            <Row>
              {!LaunchGame ? (
                <div>
                  <div className="text-without-games">
                    There are no games yet, be the first
                  </div>
                  {/*<button className="AuthMargin heading-button start-button" onClick={handleAddFriendClick}>*/}
                  {/*  <img className="play-button-icon" src={PlusIcon} alt="" />*/}
                  {/*  <div className="newgame-text">Join a Game</div>*/}
                  {/*</button>*/}
                </div>
              ) : (waitingGame ? (<Lobby changeWaitingGame={setWaitingGame} handle_GO={handleGameOver} />) : (<PongGame handleGameOver={handleGameOver} />))
              }
            </Row>
          </div>
        </Col>
      </Row>
    </Container>
  );
};

const Game = () => {
  return (
    <>
      <Header />
      <Body />
    </>
  );
};

export default Game;