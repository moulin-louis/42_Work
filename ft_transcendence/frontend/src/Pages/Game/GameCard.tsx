import Col from "react-bootstrap/Col";
import "./Game.css";
import QuanityIcon from "./icons/Quanity.svg"
import UpIcon from "./icons/Up.svg"
import RetroIcon from "./icons/Retro.svg"
import PlusIcon from "./icons/Plus.svg"
import WaitingIcon from "./icons/TimeIcon.svg"
import CloseIcon from "./icons/Close.svg"
import { useAuth } from "../../Context/AuthContext";
import React, {useContext, useEffect, useState} from "react";
import { WebSocketContext } from "../../Context/WebSocketContext";

const NewGameCard = ({ status = "default",  handleClose} : any) => {
    const { user } = useAuth();
    const socket = useContext(WebSocketContext);
    const [ game_limit, setGameLimit ] = useState("");
    const [ game_mode, setGameMode ] = useState("");
    const GameTypeBox: React.FC<{ icon: string, text: string }> = ({ icon, text }) => (
        <div className="game-type-box">
            <img style={{ width: 40, marginRight: 15 }} src={icon} alt="" />
            <div className="game-type-text">{text}</div>
        </div>
    )
    useEffect(() => {
        socket?.emit('get_info_matchamking');
        socket?.on('get_info_matchamking', (data: any): void => {
            setGameLimit(`Up to ${data.limit_max}`);
            if (data?.mode === 1) {
                setGameMode('Time mode');
                setGameLimit(`Up to ${data.limit_max} seconds`);
            }
            else {
                setGameMode('Speed mode');
                setGameLimit(`Up to ${data.limit_max} points`);
            }
        });
        return (): void => {
            socket?.off('get_info_matchamking');
        }
    }, [socket]);
    const handleCloseClick = (): void => {
        socket?.emit("quit-matchmaking");
        handleClose();
    }

    return (
        <Col xl={6} className="margin-card position-card-game" style={{ marginBottom: "30px" }}>
            {status === "waiting" && <img className="close-icon" src={CloseIcon} alt="Close" onClick={handleCloseClick} />}
            <div className='card-settings game-inline-card inline-game-card auth-shadow'>
                {
                    status === "disabled" &&
                    <div className="disabled-overlay">
                        <span>You are already waiting for an opponent</span>
                    </div>
                }
                <div className='left full-width game-vertical-align mobile-game-card'>
                    <Col xl={6}>
                        <GameTypeBox icon={QuanityIcon} text={game_limit} />
                        <GameTypeBox icon={UpIcon} text={game_mode} />
                        <GameTypeBox icon={RetroIcon} text="Retro Arcade" />
                    </Col>
                    <Col xl={6}>
                        <div className="game-inline-card">
                            <Col xl={6} className="padding-zero">
                                <div className="mobile-vertical">
                                    <img alt="" src={user?.avatar} className="game-auto-margin game-avatar" />
                                    <div className="game-nickname-card">{user?.username}</div>
                                </div>
                            </Col>
                            <Col xl={6} className="padding-zero">
                                <div className={`mobile-vertical ${status === 'default' ? 'cursor-pointer-game' : ''}`}>
                                    {status === "waiting" ?
                                        <>
                                            <img alt="" src={WaitingIcon} className="game-auto-margin game-avatar" />
                                            <div className="connect-text game-nickname-card">Waiting...</div>
                                        </>
                                        :
                                        <>
                                            <img alt="" src={PlusIcon} className="game-auto-margin game-avatar game-avatar-connect" />
                                            <div className="connect-text game-nickname-card">Connect</div>
                                        </>
                                    }
                                </div>
                            </Col>
                        </div>
                    </Col>
                </div>
            </div>
        </Col>
    )
}

export default NewGameCard;
