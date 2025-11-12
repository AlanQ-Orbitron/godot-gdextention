extends TileMapLayer

var pieceDate: Dictionary

func getPiece(coord: Vector2) -> Variant: # Dictionary
	var cellPosition: Vector2 = local_to_map(to_local(coord))
	if get_cell_source_id(cellPosition) == -1:
		return null
	else:
		pieceDate = {
			"position": cellPosition,
			"atlas": get_cell_atlas_coords(cellPosition)
		}
	
	return pieceDate

func isIllegalMove(color: float, coord: Vector2) -> bool:
	if coord.x > 7 || coord.x < 0 || coord.y > 7 || coord.y < 0:
		return true
	
	if get_cell_source_id(coord) != -1 and get_cell_atlas_coords(coord).x == color:
		return true
	return false

func moveTo(piece: Dictionary, coord: Vector2) -> bool:
	if isIllegalMove(piece.get("atlas").x, coord):
		return false
	set_cell(piece.get("position"), -1)
	set_cell(coord, 2, piece.get("atlas"))
	return true
