import "react-data-grid/lib/styles.css";
import './Help.css';
import Tabs from 'react-bootstrap/Tabs';
import Tab from 'react-bootstrap/Tab';
import Header from '../../Navigation/Header/Header';
import { Col, Container, Row } from 'react-bootstrap';
import Sidebar from "../../Navigation/Sidebar/Sidebar";

import EaleaseImage from './team-images/ealease.jpg'
import BmayerImage from './team-images/bmayer.jpg'
import LmassonImage from './team-images/lmasson.jpg'
import Llr19Img from "./../../Images/Avatar.jpg";

function GameModes() {
    return (
        <>
            <div>
                <div className='heading-help-types'>Game modes:</div>
                <ol className='numbers-help-types'>
                    <li>Classic Mode: In this mode, players compete in normal ping pong with basic rules and settings.</li>
                    <li>Speed Mode: In this mode, the speed of the ball constantly increases with each stroke, making the game of ping-pong more complex and faster.</li>
                    <li>Power-up Mode: During the game, random boosters appear on the table, which can accelerate the ball, increase or decrease its size, as well as changing the properties of the players' rackets.</li>
                    <li>Timed Mode: In this mode, players compete to see who can score more goals in a certain amount of time.</li>
                </ol>
            </div>
        </>
    )
}

function GameSkins() {
    return (
        <>
            <div>
                <div className='heading-help-types'>Game skins:</div>
                <ol className='numbers-help-types'>
                    <li>Retro Arcade: A design that recreates the atmosphere of retro video game machines, with pixelated graphics, monotone colors and simple controls.</li>
                    <li>Neon Nights: Stylized as the neon lights of a night city, with glare, flashes, bright colors and sounds, creating a dynamic atmosphere.</li>
                    <li>Abstract Art: Geometric design of the field and game elements using various recognizable styles of abstract art, such as Cubism, Impressionism or Op Art.</li>
                </ol>
            </div>
        </>
    )
}

function GameDocumentation() {
    return (
        <>
            <div>
                <div className='heading-help-types'>Introduction</div>
                <div>Welcome to Ping Pong 42, an online multiplayer game where you can compete with your friends in exhilarating ping pong matches. You can enjoy a friendly chat while playing a game and choose between different game modes for an exciting, customizable experience. This game requires the use of "w" and "s" keys on your keyboard for in-game control.</div>
                <div className='heading-help-types empty-space'>How To Play</div>
                <div>In order to control your paddle, use the following keys:</div>
                <ul className='dots-help-types small-empty-space'>
                    <li>W : Move the paddle up</li>
                    <li>S : Move the paddle down</li>
                </ul>
                <div className='small-empty-space'>The aim of the game is to hit the ball back and forth by moving your paddle up and down. The player who fails to return the ball loses a point. The game continues until one player reaches the predetermined score limit.</div>
                <div className='heading-help-types empty-space'>Conclusion</div>
                <div>Ping Pong 42 is a game of skill, precision, and quick reflexes. Each mode offers a different level of challenge, ensuring that the game remains exciting and engaging. Enjoy competing with your friends in this fast-paced, fun-filled online game! <br></br>Please refer back to this documentation for any queries regarding gameplay, controls, or rules. Happy gaming!</div>
            </div>
        </>
    )
}

function EaleaseCard() {
    return (
        <Col xl={3} className="margin-card">
            <div className='statistic-card auth-shadow'>
                <img
                    src={EaleaseImage}
                    alt=""
                    width="200"
                    height="200"
                    className="team-avatar-border align-top center-align"
                    id="navbarScrollingDropdown"
                />
                <div className="center-align empty-space"><h2 className="heading-margin">Ealease</h2></div>
                <div className='mini-badge-team'>Frontend</div>
                <div className='h-line-full empty-space'></div>
                <div className='inline empty-space'>
                    <div className="left">Campus:</div>
                    <div className='right additional-info'>Paris</div>
                </div>
                <div className='inline small-empty-space'>
                    <div className="left">Tasks:</div>
                    <div className='right additional-info'>Figma<br></br>Frontend</div>
                </div>
            </div>
        </Col>
    )
}

function BmayerCard() {
    return (
        <Col xl={3} className="margin-card">
            <div className='statistic-card auth-shadow'>
                <img
                    alt=""
                    src={BmayerImage}
                    width="200"
                    height="200"
                    className="team-avatar-border align-top center-align"
                    id="navbarScrollingDropdown"
                />
                <div className="center-align empty-space"><h2 className="heading-margin">Bmayer</h2></div>
                <div className='mini-badge-team'>Backend</div>
                <div className='h-line-full empty-space'></div>
                <div className='inline empty-space'>
                    <div className="left">Campus:</div>
                    <div className='right additional-info'>Paris</div>
                </div>
                <div className='inline small-empty-space'>
                    <div className="left">Tasks:</div>
                    <div className='right additional-info'>Chat<br></br>Friends</div>
                </div>
            </div>
        </Col>
    )
}

function LmassonCard() {
    return (
        <Col xl={3} className="margin-card">
            <div className='statistic-card auth-shadow'>
                <img
                    alt=""
                    src={LmassonImage}
                    width="200"
                    height="200"
                    className="team-avatar-border align-top center-align"
                    id="navbarScrollingDropdown"
                />
                <div className="center-align empty-space"><h2 className="heading-margin">Lmasson</h2></div>
                <div className='mini-badge-team'>Backend</div>
                <div className='h-line-full empty-space'></div>
                <div className='inline empty-space'>
                    <div className="left">Campus:</div>
                    <div className='right additional-info'>Paris</div>
                </div>
                <div className='inline small-empty-space'>
                    <div className="left">Tasks:</div>
                    <div className='right additional-info'>Settings<br></br>Friends</div>
                </div>
            </div>
        </Col>
    )
}

function Llr19Card() {
    return (
        <Col xl={3} className="margin-card">
            <div className='statistic-card auth-shadow'>
                <img
                    alt=""
                    src={Llr19Img}
                    width="200"
                    height="200"
                    className="team-avatar-border align-top center-align"
                    id="navbarScrollingDropdown"
                />
                <div className="center-align empty-space"><h2 className="heading-margin">Llr19</h2></div>
                <div className='mini-badge-team'>Backend</div>
                <div className='h-line-full empty-space'></div>
                <div className='inline empty-space'>
                    <div className="left">Campus:</div>
                    <div className='right additional-info'>Paris</div>
                </div>
                <div className='inline small-empty-space'>
                    <div className="left">Tasks:</div>
                    <div className='right additional-info'>Game</div>
                </div>
            </div>
        </Col>
    )
}

function HelpBlock() {
    return (
        <>
            <Container>
                <div className="help-page">
                    <Tabs>
                        <Tab eventKey="friends"
                            title={<>Documentation</>}
                            className="friends-table"
                        >
                            <GameDocumentation />
                        </Tab>
                        <Tab eventKey="types"
                            title={<>Game modes</>}
                            className="friends-table"
                        >
                            <GameModes />
                        </Tab>
                        <Tab eventKey="skins"
                            title={<>Game skins</>}
                            className="friends-table"
                        >
                            <GameSkins />
                        </Tab>
                        <Tab eventKey="online"
                            title={<>Developers</>}
                            className="friends-table"
                        >
                            <div className='row'>
                                <EaleaseCard />
                                <BmayerCard />
                                <LmassonCard />
                                <Llr19Card />
                            </div>
                        </Tab>
                    </Tabs>
                </div>
            </Container>
        </>
    );
}


function Help() {
    return (
        <>
            <Header />
            <Container>
                <Row className="zero-margin">
                    <Col lg={12} xl={2} className="sidebar-global">
                        <Sidebar />
                    </Col>
                    <Col lg={12} xl={10}>
                        <div className="content">
                            <Row>
                                <Col xl={12}>
                                    <div className='inline'>
                                        <div className="left"><h1 className="heading heading-margin">Help</h1></div>
                                    </div>
                                </Col>
                            </Row>
                            <Row>
                                <Col xl={12} className="margin-card" style={{ marginBottom: "30px" }}>
                                    <HelpBlock />
                                </Col>
                            </Row>
                        </div>
                    </Col>
                </Row>
            </Container>
        </>
    )
}

export default Help;