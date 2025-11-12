extends Node2D

@onready var highlights: TileMapLayer = $Highlights
@onready var chess_pieces: TileMapLayer = $ChessPieces
@onready var pieces: AnimatedSprite2D = $Pieces

var selectedPiece: Variant # Dictionary
var isSelectedNull: bool

enum pieaces {
	Pawn,
	Rook,
	Knight,
	Biship,
	Queen,
	King
}

enum color {
	Black,
	White
}

func _input(event: InputEvent) -> void:
	if event.is_action_pressed("MB1"):
		selectedPiece = chess_pieces.getPiece(get_global_mouse_position())
		if selectedPiece == null:
			pieces.hide()
			isSelectedNull = true
		else:
			pieces.show()
			isSelectedNull = false
			chess_pieces.set_cell(selectedPiece.get("position"), -1)
			match selectedPiece.get("atlas").x:
				0:
					pieces.animation = "Black"
				1:
					pieces.animation = "White"
			pieces.frame = selectedPiece.get("atlas").y
	
	if event.is_action_released("MB1"):
		pieces.hide()
		if !isSelectedNull:
			if !chess_pieces.moveTo(selectedPiece, chess_pieces.local_to_map(to_local(get_global_mouse_position()))):
				chess_pieces.set_cell(selectedPiece.get("position"), 2, selectedPiece.get("atlas"))

func _ready() -> void:
	pass
	#chess_pieces.moveTo([Vector2(color.Black, pieaces.King), Vector2(0, 3)], Vector2(0, 0))
