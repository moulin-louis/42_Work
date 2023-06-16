import { useContext, useState } from "react";
import { WebSocketContext } from "../../Context/WebSocketContext";
import "./Game.css";

import OverlayTrigger from "react-bootstrap/OverlayTrigger";
import Tooltip from "react-bootstrap/Tooltip";
import AlertIcon from "./../../Images/Alert.svg";

import Col from "react-bootstrap/Col";
import Row from "react-bootstrap/Row";

function AlertInfo(alertMessage: string) {
    return (
        <>
            <OverlayTrigger
                key={'left'}
                placement={'left'}
                overlay={
                    <Tooltip id={`tooltip-${'left'}`}>
                        <div style={{ textAlign: "left" }}>
                            Modes:<br></br>
                            1) Classic: Standard ping pong rules.<br></br>
                            2) Speed: Ball speed increases each stroke, making the game faster and more complex.<br></br>
                            3) Power-up: Random boosters appear, affecting ball speed, size and racket properties.<br></br>
                            4) Timed: Players aim to score as many goals as possible within a time limit.<br></br>
                        </div>
                    </Tooltip>
                }
            >
                <div className="right"><img
                    alt=""
                    src={AlertIcon}
                    width="30"
                    height="30"
                    className="alert-icon-margin"
                    id="navbarScrollingDropdown"
                /></div>
            </OverlayTrigger>
        </>
    );
}

/**
 * Component to display and add to friends users.
 *
 * @param onClose - Function to call when closing the member display
 * @param users - The users being displayed and managed
 */
function PopupNewGame({
    onClose,
    startMatchmaking,
}: {
    onClose: () => void;
    startMatchmaking: () => void;
}) {
    const socket = useContext(WebSocketContext);

    const handleAdd = (userId: string) => {
        socket?.emit("addtofriends", {});
        onClose();
    };

    const [name, setName] = useState<string>("");
    const [secret, setSecret] = useState<boolean>(false);
    const [password, setPassword] = useState<string>("");
    const [checkboxClass, setCheckboxClass] = useState<string>(
        "chat-popup-checkbox"
    );

    // Define game modes
    const gameModes = [
        { id: 'classic', name: 'Classic mode' },
        { id: 'speed', name: 'Speed mode' },
        { id: 'power', name: 'Power-Up mode' },
        { id: 'timed', name: 'Timed mode' },
    ];

    // Define game skins
    const gameSkins = [
        { id: 'retro', name: 'Retro Arcade' },
        { id: 'neon', name: 'Neon Nights' },
        { id: 'abstract', name: 'Abstract Art' },
    ];

    // Define wins options
    const winsOptions = [
        { id: 'up_to_3_wins', name: 'Up to 3 wins' },
        { id: 'up_to_11_wins', name: 'Up to 11 wins' },
    ];

    // State for tracking the selected game mode with first mode as default
    const [selectedMode, setSelectedMode] = useState<string>(gameModes[0].id);

    // State for tracking the selected game skin with first skin as default
    const [selectedSkin, setSelectedSkin] = useState<string>(gameSkins[0].id);

    // State for tracking the selected wins option with first option as default
    const [selectedWins, setSelectedWins] = useState<string>(winsOptions[0].id);

    const handleModeChange = (mode: string) => {
        setSelectedMode(mode);
    }

    const handleSkinChange = (skin: string) => {
        setSelectedSkin(skin);
    }

    const handleWinsChange = (winsOption: string) => {
        setSelectedWins(winsOption);
    }

    // function to select random item from an array
    const selectRandom = (array: any[]) => array[Math.floor(Math.random() * array.length)].id;

    // function to select random game mode, skin and win option
    const randomChoose = () => {
        setSelectedMode(selectRandom(gameModes));
        setSelectedSkin(selectRandom(gameSkins));
        setSelectedWins(selectRandom(winsOptions));
    }

    return (
        <div className="zero-margin">
            <div className="chat-popup-window">
                <div className="popup-header game-inline-card">
                    <h4 className="game-popup-big-head">Create game</h4>
                    <button className="random-choose-button" onClick={randomChoose}>Random</button>
                </div>
                <div className="chat-full-width">
                    <div className="chat-popup-head chat-popup-new-game">
                        <div>Choose a game mode:</div>
                        <div className="tooltip-popup">
                            {AlertInfo("Modes:\nClassic Mode: In this mode, players compete in normal ping pong with basic rules and settings.<br></br>Speed Mode: In this mode, the speed of the ball constantly increases with each stroke, making the game of ping-pong more complex and faster.<br></br>Power-up Mode: During the game, random boosters appear on the table, which can accelerate the ball, increase or decrease its size, as well as changing the properties of the players' rackets.<br></br>Timed Mode: In this mode, players compete to see who can score more goals in a certain amount of time.")}
                        </div>
                    </div>
                    <div className="game-inline-card">
                        <Row className="g-2 full-width-cards">
                            {gameModes.map(mode => (
                                <Col xl={6} key={mode.id}>
                                    <div
                                        className={selectedMode === mode.id ? "chat-popup-checkbox-changed" : "chat-popup-checkbox"}
                                        onClick={() => handleModeChange(mode.id)}
                                    >
                                        <input
                                            type="checkbox"
                                            checked={selectedMode === mode.id}
                                            style={{ marginRight: "15px" }}
                                        />
                                        {mode.name}
                                    </div>
                                </Col>
                            ))}
                        </Row>
                    </div>
                </div>
                <div className="chat-full-width">
                    <div className="chat-popup-head chat-popup-new-game">
                        <div>Pick a skin of the game:</div>
                    </div>
                    <div className="game-inline-card">
                        <Row className="g-2 full-width-cards">
                            {gameSkins.map(skin => (
                                <Col xl={6} key={skin.id}>
                                    <div
                                        className={selectedSkin === skin.id ? "chat-popup-checkbox-changed" : "chat-popup-checkbox"}
                                        onClick={() => handleSkinChange(skin.id)}
                                    >
                                        <input
                                            type="checkbox"
                                            checked={selectedSkin === skin.id}
                                            style={{ marginRight: "15px" }}
                                        />
                                        {skin.name}
                                    </div>
                                </Col>
                            ))}
                        </Row>
                    </div>
                </div>
                <div className="chat-full-width">
                    <div className="chat-popup-head chat-popup-new-game">
                        <div>How many wins to play:</div>
                    </div>
                    <div className="game-inline-card">
                        <Row className="g-2 full-width-cards">
                            {winsOptions.map(winsOption => (
                                <Col xl={6} key={winsOption.id}>
                                    <div
                                        className={selectedWins === winsOption.id ? "chat-popup-checkbox-changed" : "chat-popup-checkbox"}
                                        onClick={() => handleWinsChange(winsOption.id)}
                                    >
                                        <input
                                            type="checkbox"
                                            checked={selectedWins === winsOption.id}
                                            style={{ marginRight: "15px" }}
                                        />
                                        {winsOption.name}
                                    </div>
                                </Col>
                            ))}
                        </Row>
                    </div>
                </div>
                <div>
                    <div style={{ marginTop: "45px", display: "flex" }}>
                        <button className="chat-popup-button-blue" onClick={() => { startMatchmaking(); onClose(); }}>
                            Create game
                        </button>
                        <button
                            className="chat-popup-button-white"
                            type="button"
                            onClick={onClose}
                        >
                            Cancel
                        </button>
                    </div>
                </div>
            </div>
        </div>
    );
}

export default PopupNewGame;