enum SelectionType { None, Start, End, WallEndpoint };

class SelectionState {
public:
	SelectionState() {}
	Vec2f prevPosition;
	SelectionType selectionType = None;
	int wallIdx;
	int wallEndpoint;
	bool dragging = false;
};
