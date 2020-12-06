'use strict';


const e = React.createElement;
const updateIntervalMillis = 30;

function isNumeric(str) {
	if (typeof str != "string") return false
	return !isNaN(str) && 
	!isNaN(parseFloat(str)) 
}
	
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
				time: 0,
				timeStep: 1
			},
			paused: true,
			mode: "edit",
			path: null,
			selection: null,
			dragging: false
		};
		setInterval(() => {
			if(this.state.paused == false && this.state.path != null) {
				var st = this.state;
				st.env.time += updateIntervalMillis / 1000;
				if(st.env.time > this.state.path.getArriveTime()) {
					st.env.time = this.state.path.getArriveTime();
				}
				this.setState(st);
			}
		}, updateIntervalMillis);
		this.state.wallCount = this.state.env.walls.length;
		document.addEventListener("keydown", this.onKeyDown);
	}

	setSelectionPos = (pos) => {
		var e = this.state.env;
		if(this.state.selection == "start") {
			e.start.x = pos.x;
			e.start.y = pos.y;
		} else if(this.state.selection == "end") {
			e.end.x = pos.x;
			e.end.y = pos.y;
		} else if(this.state.selection != null && this.state.selection.lineId != null && this.state.selection.endpoint != null) {
			e.walls.map(wall =>
				{
					if(wall.id == this.state.selection.lineId) {
						wall[this.state.selection.endpoint].x = pos.x;
						wall[this.state.selection.endpoint].y = pos.y;
					}
					return wall;
				}
			);
		}
		this.setState({ env: e, path: null });
	}

	getSelectedAttributes = () => {
		var e = this.state.env;
		if(this.state.selection == "start") {
			return e.start;
		} else if(this.state.selection == "end") {
			return e.end;
		} else if(this.state.selection != null && this.state.selection.lineId != null && this.state.selection.endpoint != null) {
			return e.walls.filter(wall => { return wall.id == this.state.selection.lineId; } )[0][this.state.selection.endpoint]; 
		}
		return {};
	}

	computePath = () => {
		var wallVector = new Module.vector$Wall$;
		var walls = this.state.env.walls.map(wall =>
			new Module.Wall(
				new Module.Point(wall.point1.x, wall.point1.y, wall.point1.vx, wall.point1.vy),
				new Module.Point(wall.point2.x, wall.point2.y, wall.point2.vx, wall.point2.vy))).forEach(wall => wallVector.push_back(wall));
		var dypfEnv = new Module.Environment(this.state.env.start, this.state.env.end, wallVector, this.state.env.speed, this.state.env.timeStep);
		var solver = new Module.Solver(Module.getEnvironmentPointer(dypfEnv));
		var path = solver.solve();
		this.setState({path});
	}

	setMode = (mode) => {
		this.setState({ mode, selection: null });
	}

	onPlayClicked = () => {
		this.setState({ paused: false, mode: "pan", selection: null });
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
		st.mode = "pan";
		st.env.time =  0;
		this.setState(st);
	}

	onMouseDown = (point) => {
		if(this.state.mode == "edit") {
			this.setState({ selection: point, dragging: true });
		}
	}

	onMouseUp = () => {
		this.setState({ dragging: false });
	}

	onMouseMove = (pos) => {
		if(this.state.paused && this.state.selection != null && this.state.mode == "edit" && this.state.dragging) {
			this.setSelectionPos(pos);
		}
	}

	onMouseClick = (point) => {
		if(this.state.mode == "edit") {
			this.setState({ selection: point });
		}
	}

	wallStart = (pos) => {
		this.wallPoint1 = { x: pos.x, y: pos.y, vx: 0, vy: 0 };
		this.setState( { path: null } );
	}

	wallEnd = (pos) => {
		var wall = {
			id: this.state.wallCount,
			point1: this.wallPoint1,
			point2: { x: pos.x, y: pos.y, vx: 0, vy: 0 }
		};
		var env = this.state.env;
		env.walls.push(wall);
		this.setState( { env, wallCount: this.state.wallCount + 1 } );
	}

	onInputChanged = (field, value) => {
		if(!isNumeric(value)) return;
		var v = parseFloat(value);
		var env = this.state.env;
		if(field == "speed" || field == "timeStep") {
			env[field] = v;
		} else if(this.state.selection == "start") {
				env.start[field] = v;
		} else if(this.state.selection == "end") {
				env.end[field] = v;
		} else if(this.state.selection != null && this.state.selection.lineId != null && this.state.selection.endpoint != null) {
			env.walls.map(wall =>
				{
					if(wall.id == this.state.selection.lineId) {
						wall[this.state.selection.endpoint][field] = v;
					}
					return wall;
				}
			);
		}
		this.setState({ env, path: null })
	}
	
	onKeyDown = (ev) => {
		if(ev.key === "Backspace") {
			if(this.state.selection != null && this.state.selection.lineId != null) {
				var env = this.state.env;
				env.walls = env.walls.filter(wall => wall.id != this.state.selection.lineId);
				this.setState({ env, selection: null, path: null });
			}
		}
	}

	render() {
		return (
			<div className="container" onKeyDown={this.onKeyDown}>
				<div className="row"><div className="col">
					<ControlBar env={this.state.env} mode={this.state.mode} setMode={this.setMode} selectedAttributes={this.getSelectedAttributes()} onInputChanged={this.onInputChanged}/>
				</div></div>
				<div className="row"><div className="col">
					<Display env={this.state.env} path={this.state.path} mode={this.state.mode} selection={this.state.selection}
						wallStart={this.wallStart} wallEnd={this.wallEnd}
						onMouseMove={this.onMouseMove} onMouseDown={this.onMouseDown} onMouseUp={this.onMouseUp} onMouseClick={this.onMouseClick}/>
				</div></div>
				<div className="row"><div className="col">
					<PlayBar env={this.state.env}
						onPlayClicked={this.onPlayClicked} onPauseClicked={this.onPauseClicked} onResetClicked={this.onResetClicked}
						paused={this.state.paused} onInputChanged={this.onInputChanged}/>
				</div></div>
			</div>
		);
	}
}

const domContainer = document.querySelector('#app_container');
var app = React.createElement(App);
ReactDOM.render(app, domContainer);
