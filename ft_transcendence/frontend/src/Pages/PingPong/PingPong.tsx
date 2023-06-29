import "react-data-grid/lib/styles.css";
import './PingPong.css';
import { Col, Container, Row } from 'react-bootstrap';
import QuanityIcon from "./../Game/icons/Quanity.svg"
import UpIcon from "./../Game/icons/Up.svg"
import RetroIcon from "./../Game/icons/Retro.svg"
import Logo from "./../../Images/Logo.svg";
import avatarExample from "./pingpong-images/ealease.jpg"
import UserImg from './../Auth/img/Avatar.jpg'

import { PongGame } from "./../Game/Game"

function WatchersInfo() {
    return <div className="watchers">
        <div className="auth-avatars-margin">
            <img className="auth-avatar-circle" src={UserImg} alt="" />
            <img className="auth-avatar-circle" src={UserImg} alt="" />
            <img className="auth-avatar-circle" src={UserImg} alt="" />
        </div>
        <div>
            14 game watchers
        </div>
    </div>;
}


function UsersInfo() {
    return (
        <>
            <div className="game-inline-card user-gamers-block">
                <div className="padding-zero">
                    <img
                        alt=""
                        src={avatarExample}
                        className="game-auto-margin game-avatar game-avatar-empty"
                    />
                    <div className="game-nickname-card">Nickname</div>
                </div>
                <div className="watchers-margin">
                    <WatchersInfo />
                </div>
                <div className="padding-zero">
                    <img
                        alt=""
                        src={avatarExample}
                        className="game-auto-margin game-avatar game-avatar-empty"
                    />
                    <div className="game-nickname-card">Nickname</div>
                </div>
            </div>
        </>
    );
}

function GameType() {
    return (
        <>
            <div className="game-type-box-history">
                <div className="type-game-pp">
                    <img
                        style={{ width: 40, marginRight: 15 }}
                        src={QuanityIcon}
                        alt="Quanity"
                    />
                    <div>Up to 3 wins</div>
                </div>
                <div className="type-game-pp">
                    <img
                        style={{ width: 40, marginRight: 15 }}
                        src={UpIcon}
                        alt="Quanity"
                    />
                    <div>Classic Mode</div>
                </div>
                <div className="type-game-pp">
                    <img
                        style={{ width: 40, marginRight: 15 }}
                        src={RetroIcon}
                        alt="Quanity"
                    />
                    <div>Retro Arcade</div>
                </div>
            </div>
        </>
    )
}

function PingPong() {
    const handleClick = () => {
    };

    return (
        <>
            {/* <Header /> */}
            <Container className="background-pong">
                <Row className="zero-margin">
                    <Col lg={12} xl={12}>
                        <div className="content">
                            <Row>
                                <div className='inline pong-header'>
                                    <div className="left"><img className="auth-logo-center logo-ping-pong" src={Logo} alt="Logo" /></div>
                                    <div className="right button-margin">
                                        <div className="button-return" onClick={handleClick}>Give up and return</div>
                                    </div>
                                </div>
                            </Row>
                            <Row className="game-area">
                                <GameType />
                                <Col xl={12}>
                                    <PongGame />
                                </Col>
                                <Col xl={12} className="margin-card" style={{ marginBottom: "30px" }}>
                                    <UsersInfo />
                                </Col>
                            </Row>
                        </div>
                    </Col>
                </Row>
            </Container>
        </>
    )
}

export default PingPong;