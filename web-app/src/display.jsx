'use strict'

class Display extends React.Component {
	constructor(props) {
		super(props);
		this.state = {};
	}

	componentDidMount() {
		this.pt = this.svg.createSVGPoint();
	}

	pathPos = () => {
		if(this.props.path != null) {
			var pos = this.props.path.getPos(this.props.env.time);
			return <circle cx={pos.x} cy={pos.y} r="5" fill="black" />
		}
		return null;
	}

	mouseDown = (point) => {
		return () => this.props.onMouseDown(point);
	}

	mouseUp = () => {
		this.props.onMouseUp();
	}

	mouseMove = (ev) => {
		this.pt.x = ev.clientX;
		this.pt.y = ev.clientY;
		
		// The cursor point, translated into svg coordinates
		var cursorpt =  this.pt.matrixTransform(this.svg.getScreenCTM().inverse());
		this.props.onMouseMove(cursorpt);
	}

	render() {
		 return (
			<svg id="display" width="1080" height="600" style={{ border: '3px solid #000000' }} ref={(ref) => this.svg = ref} onMouseMove={ this.mouseMove }>
				<circle cx={this.props.env.start.x} cy={this.props.env.start.y} r="10" stroke="black" strokeWidth="2" fill="green" onMouseDown={ this.mouseDown("start") } onMouseUp={ this.mouseUp } />
				<circle cx={this.props.env.end.x} cy={this.props.env.end.y} r="10" stroke="black" strokeWidth="2" fill="red" onMouseDown={ this.mouseDown("end") } onMouseUp={ this.mouseUp } />
			 	{ this.props.env.walls.map(wall => (
					<React.Fragment key={wall.id} >
						<line x1={wall.point1.x + this.props.env.time * wall.point1.vx}
							y1={wall.point1.y + this.props.env.time * wall.point1.vy}
							x2={wall.point2.x + this.props.env.time * wall.point2.vx}
							y2={wall.point2.y + this.props.env.time * wall.point2.vy}
							stroke="black" strokeWidth="2"/>
						<circle cx={wall.point1.x + this.props.env.time * wall.point1.vx}
							cy={wall.point1.y + this.props.env.time * wall.point1.vy}
							r="5" stroke="black" strokeWidth="2" fillOpacity="0"
							onMouseDown={ this.mouseDown({ lineId: wall.id, endpoint: "point1" }) } onMouseUp={ this.mouseUp } />
						<circle cx={wall.point2.x + this.props.env.time * wall.point2.vx}
							cy={wall.point2.y + this.props.env.time * wall.point2.vy}
							r="5" stroke="black" strokeWidth="1" fillOpacity="0"
							onMouseDown={ this.mouseDown({ lineId: wall.id, endpoint: "point2" }) } onMouseUp={ this.mouseUp } />
					</React.Fragment>
				)) }
			 	{ this.pathPos() }
			</svg>
		 );
	}

}
