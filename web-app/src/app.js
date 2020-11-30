'use strict';

const e = React.createElement;

class LikeButton extends React.Component {
	constructor(props) {
		super(props);
		this.state = {};
	}

	render() {
		return <h1>Hello!</h1>;
	}
}


const domContainer = document.querySelector('#app_container');
ReactDOM.render(e(LikeButton), domContainer);
