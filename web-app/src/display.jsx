'use strict'

class Display extends React.Component {
	constructor(props) {
		super(props);
		this.state = {};
	}

	render() {
		 return (
			<svg id="display" width="1080" height="600" style={{border: '3px solid #000000'}}>
				<circle cx={this.props.env.start.x} cy={this.props.env.start.y} r="10" stroke="black" strokeWidth="2" fill="green" />
				<circle cx={this.props.env.end.x} cy={this.props.env.end.y} r="10" stroke="black" strokeWidth="2" fill="red" />
			 	{ this.props.env.walls.map(wall => <line key={wall.id}
					x1={wall.point1.x + this.props.env.time * wall.point1.vx}
					y1={wall.point1.y + this.props.env.time * wall.point1.vy}
					x2={wall.point2.x + this.props.env.time * wall.point2.vx}
					y2={wall.point2.y + this.props.env.time * wall.point2.vy} stroke="black" strokeWidth="2" />) }
			</svg>
		 );
	}

}
