import React, { useContext, useState, useEffect } from "react";
import { WebSocketContext } from "../../Context/WebSocketContext";
import { Socket } from "socket.io-client";
import "./Chat.css";

const GameProposal = ({onClose}: { onClose: () => void }): React.JSX.Element => {
  const socket = useContext<Socket | undefined>(WebSocketContext);
  const [game_mode, setGameMode] = useState<string>("");
  const [limit_max, setLimitMax] = useState<number>(0);
  const acceptGP = (): void => {
    socket?.emit('accept_game_proposal');
    onClose();
  };
  const refuseGP = (): void => {
    socket?.emit('refuse_game_proposal');
    onClose();
  }
  useEffect(() => {
    socket?.emit('get_game_proposal');
    socket?.on('get_game_proposal', (payload: { game_mode:string, limit_max:number }) => {
      setGameMode(payload.game_mode);
      setLimitMax(payload.limit_max);
    });
    return (): void => { socket?.off('get_game_proposal');}
  }, [socket]);
  return (
    <div className="chat-popup-window">
      <h3 className="chat-popup-head">Accept invitation to a game in {game_mode === "speed" ? "speed mode" : "time mode"} with a limit of {game_mode === "speed" ? limit_max + ' points' : limit_max * 10 + 's'} ? </h3>
      <div style={{ marginTop: "45px", display: "flex" }}>
        <button
          className="chat-popup-button-white"
          type="button"
          onClick={refuseGP}
        >
          Refuse
        </button>
        <button
          className="chat-popup-button-blue"
          type="button"
          onClick={acceptGP}
        >
          Accept
        </button>
      </div>
    </div>
    );
}

export default GameProposal;
