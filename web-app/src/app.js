'use strict';


const e = React.createElement;
const updateIntervalMillis = 30;

class App extends React.Component {
	constructor(props) {
		super(props);
		this.state = {
			env: {
				start: {x: 50, y:50},
				end: {x:350, y:250},
				walls: [
					{
						id: 0,
						point1: {x: 100, y: 50, vx: 0, vy: 20},
						point2: {x: 100, y: 150, vx: 20, vy: 0}
					}
				],
				speed: 25,
				time: 0
			},
			paused: true,
			path: null
		};
		setInterval(() => {
			if(this.state.paused == false && this.state.path != null) {
				var st = this.state;
				st.env.time += updateIntervalMillis / 1000;
				this.setState(st);
			}
		}, updateIntervalMillis);
	}

	computePath = () => {
		var wallVector = new Module.vector$Wall$;
		var walls = this.state.env.walls.map(wall =>
			new Module.Wall(
				new Module.Point(wall.point1.x, wall.point1.y, wall.point1.vx, wall.point1.vy),
				new Module.Point(wall.point2.x, wall.point2.y, wall.point2.vx, wall.point2.vy))).forEach(wall => wallVector.push_back(wall));
		var dypfEnv = new Module.Environment(this.state.env.start, this.state.env.end, wallVector, this.state.env.speed, 1);
		var solver = new Module.Solver(Module.getEnvironmentPointer(dypfEnv));
		var path = solver.solve();
		this.setState({path});
	}

	onPlayClicked = () => {
		this.setState({ paused: false });
		if(this.state.path == null) {
			this.computePath();
		}
	}

	onPauseClicked = () => {
		this.setState({ paused: true });
	}

	onResetClicked = () => {
		var st = this.state;
		st.paused = true;
		st.env.time =  0;
		this.setState(st);
	}

	render() {
		return (
			<React.Fragment>
				<div className="row"><div className="col"><ControlBar /></div></div>
				<div className="row"><div className="col"><Display env={this.state.env} path={this.state.path}/></div></div>
				<div className="row"><div className="col">
					<PlayBar onPlayClicked={this.onPlayClicked} onPauseClicked={this.onPauseClicked} onResetClicked={this.onResetClicked} paused={this.state.paused}/>
				</div></div>
			</React.Fragment>
		);
	}
}

const domContainer = document.querySelector('#app_container');
ReactDOM.render(React.createElement(App), domContainer);
