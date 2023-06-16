import Col from "react-bootstrap/Col";
import "./../Game/Game.css";
import QuanityIcon from "./../Game/icons/Quanity.svg"
import UpIcon from "./../Game/icons/Up.svg"
import RetroIcon from "./../Game/icons/Retro.svg"
import PlusIcon from "./../Game/icons/Plus.svg"
import { useAuth } from "../../Context/AuthContext";

function NewHistoryCard() {
    const { user } = useAuth();

    return (
        <>
            <Col xl={6} className="margin-card" style={{ marginBottom: "30px" }}>
                <div className='card-settings game-inline-card inline-achievements auth-shadow'>
                    <div className='left full-width game-vertical-align'>
                        <Col xl={6}>
                            <div className="game-type-box">
                                <img
                                    style={{ width: 40, marginRight: 15 }}
                                    src={QuanityIcon}
                                    alt="Quanity"
                                />
                                <div className="game-type-text">
                                    Up to 3 wins
                                </div>
                            </div>
                            <div className="game-type-box">
                                <img
                                    style={{ width: 40, marginRight: 15 }}
                                    src={UpIcon}
                                    alt="Quanity"
                                />
                                <div className="game-type-text">
                                    Power-up Mode
                                </div>
                            </div>
                            <div className="game-type-box">
                                <img
                                    style={{ width: 40, marginRight: 15 }}
                                    src={RetroIcon}
                                    alt="Quanity"
                                />
                                <div className="game-type-text">
                                    Retro Arcade
                                </div>
                            </div>
                        </Col>
                        <Col xl={6}>
                            <div className="game-inline-card">
                                <Col xl={6}>
                                    <Col lg={12} xl={12} className="padding-zero">
                                        <div className="mobile-vertical">
                                            <div>
                                                <img
                                                    alt=""
                                                    src={user?.avatar}
                                                    className="game-auto-margin game-avatar"
                                                />
                                            </div>
                                            <div>
                                                <div className="game-nickname-card username-header-text">{user?.username}</div>
                                            </div>
                                        </div>
                                    </Col>
                                </Col>
                                <Col xl={6}>
                                    <Col lg={12} xl={12} className="padding-zero">
                                        <div className="mobile-vertical cursor-pointer-game">
                                            <div>
                                                <img
                                                    alt=""
                                                    src={PlusIcon}
                                                    className="game-auto-margin game-avatar game-avatar-connect"
                                                />
                                            </div>
                                            <div>
                                                <div className="connect-text game-nickname-card username-header-text">Connect</div>
                                            </div>
                                        </div>
                                    </Col>
                                </Col>
                            </div>
                        </Col>
                    </div>
                </div>
            </Col>
        </>
    )
}

export default NewHistoryCard;