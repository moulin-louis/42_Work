import { useState, useEffect, useContext, useRef } from "react";
import { WebSocketContext } from "../../Context/WebSocketContext";
import { Socket } from "socket.io-client";
import Header from "./../../Navigation/Header/Header";
import Sidebar from "./../../Navigation/Sidebar/Sidebar";
import Container from "react-bootstrap/Container";
import Row from "react-bootstrap/Row";
import Col from "react-bootstrap/Col";
import "./Game.css";
import PlayIcon from "./../../Navigation/Sidebar/icons/Cart.svg";
import PlusIcon from "./icons/PlusBlue.svg";
import NewGameCard from "./GameCard";
import PopupNewGame from "./GamePopup"

interface IPosition {
  x: number;
  y: number;
}

interface FuncProps {
  changeWaitingGame(new_state: boolean): void;
}

enum GameState {
  WIN,
  LOSE,
};

// this function is used to handle socket events
const useSocketEvent = (socket: Socket | undefined, event: string, handler: any) => {
  useEffect(() => {
    socket?.on(event, handler);
    return () => {
      socket?.off(event);
    };
  }, [socket, event, handler]);
}

// This code creates a paddle that is updated when the server sends a new position.
const usePaddle: any = (eventKey: any, color: string, className: string) => {
  const socket = useContext(WebSocketContext);
  const [position, setPosition] = useState<IPosition>({ x: 0, y: 0 });
  useSocketEvent(socket, eventKey, (payload: IPosition) => {
    setPosition(payload)
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
// The "Move" event is emitted when the w or s keys are pressed.
const PlayerBar = () => {
  const paddleProps = usePaddle("Player_Position", "green", "paddle left");
  const socket = useContext(WebSocketContext);
  const keysRef = useRef(new Set());
  useEffect(() => {
    const handleKeyDown = (event: any) => {
      keysRef.current.add(event.key);
    };
    const handleKeyUp = (event: any) => {
      keysRef.current.delete(event.key);
    };
    document.body.addEventListener('keydown', handleKeyDown);
    document.body.addEventListener('keyup', handleKeyUp);
    return () => {
      document.body.removeEventListener('keydown', handleKeyDown);
      document.body.removeEventListener('keyup', handleKeyUp);
    };
  }, []);
  useEffect(() => {
    const intervalId = setInterval(() => {
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
const EnemyBar = () => {
  const paddleProps = usePaddle("EnemyPos", "red", "paddle right");
  return (
    <div {...paddleProps}></div>
  );
};

// This code gets the score of the player from the server and sets it to the correct score
const PlayerScore = () => {
  const socket = useContext(WebSocketContext);
  const [score, setScore] = useState<number>(0);

  useSocketEvent(socket, "PlayerScore", (payload: number) => setScore(payload));
  return <div className="score left">{score}</div>;
};

// This code gets the score of the enemy from the server and sets it to the correct score
const EnemyScore = () => {
  const socket = useContext(WebSocketContext);
  const [score, setScore] = useState<number>(0);

  useSocketEvent(socket, "EnemyScore", (payload: number) => setScore(payload));
  return <div className="score right">{score}</div>;
};

// This code gets the position of the ball from the server and sets it to the correct position
const Ball = () => {
  const socket = useContext(WebSocketContext);
  const [position, setPosition] = useState<IPosition>({ x: 180, y: 300 });

  useSocketEvent(socket, "GetPositionBall", (payload: IPosition) => setPosition(payload));
  return (
    <svg width={600} height={400}>
      <circle cx={position.x} cy={position.y} r="10" fill="black" />
    </svg>
  );
};

const GameOver = ({ status }: any) => {
  return (
    <div className="game-over">
      {status === GameState.WIN ? (<h1> You win !</h1>) : (<h1> You lose !</h1>)}
    </div>
  )
}

// This code creates the game board
const PongGame = () => {
  const [game_state, setGameState] = useState<GameState | null>(null);
  const [game_ended, setGameEnded] = useState<boolean>(false);
  const socket = useContext(WebSocketContext);
  useSocketEvent(socket, "GameOver", (payload: any) => {
    if (payload.winner === 'you') {
      setGameEnded(true);
      setGameState(GameState.WIN);
    } else if (payload.winner === 'not_you') {
      setGameEnded(true);
      setGameState(GameState.LOSE);
    }
  });
  return (
    <div className="game-board">
      {game_ended ? <GameOver status={game_state} /> : (
        <div>
          <PlayerBar />
          <EnemyBar />
          <PlayerScore />
          <EnemyScore />
          <Ball />
        </div>
      )
      }
    </div>
  );
};

// This code creates the game lobby, waiting in matchmaking room for a player
const Lobby: React.FC<FuncProps> = ({ changeWaitingGame }: FuncProps) => {
  const socket = useContext(WebSocketContext);
  useSocketEvent(socket, "matchmaking", (payload: boolean) => { if (payload) changeWaitingGame(false); });
  return (
    <div className="lobby">
      <h1>Waiting for a player to join...</h1>
    </div>
  );
};

// This function is used to handle the game state of the user.
// It is used to start the matchmaking process, and to handle when the game is over.
// It also handles the waiting state of the user, when the user is waiting for an opponent.
const useGameState = () => {
  const [LaunchGame, setLaunchGame] = useState(false);
  const [waitingGame, setWaitingGame] = useState<boolean>(true);
  const socket = useContext(WebSocketContext);
  useEffect(() => {
    const handleGameOver = (payload: any) => {
      setLaunchGame(false);
      setWaitingGame(true);
    }
    const handleMatchmaking = (payload: boolean) => {
      if (payload === true) setWaitingGame(false);
    }
    socket?.on("GameOver", handleGameOver);
    socket?.on("matchmaking", handleMatchmaking);
  }, [socket]);
  const startMatchmaking = () => {
    socket?.emit("matchmaking");
    setLaunchGame(true);
  }
  return { LaunchGame, waitingGame, startMatchmaking, setWaitingGame };
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

const Body = () => {
  const { LaunchGame, waitingGame, startMatchmaking, setWaitingGame } = useGameState();
  const [showChannelMembers, setShowChannelMembers] = useState(false);

  const handleAddFriendClick = () => {
    setShowChannelMembers(true);
  };

  const handleClose = () => {
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
                  <button className="AuthMargin heading-button start-button" onClick={startMatchmaking}>
                    <img className="play-button-icon" src={PlusIcon} alt="" />
                    <div className="newgame-text">Join a Game</div>
                  </button>
                </div>
              ) : (waitingGame ? (<Lobby changeWaitingGame={setWaitingGame} />) : (<PongGame />))
              }
            </Row>
            <Row style={{ marginTop: "45px" }}>
              <NewGameCard status="waiting" />
              <NewGameCard status="disabled" />
              <NewGameCard status="default" />
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