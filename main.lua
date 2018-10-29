local player = {
	image = image("assets/player.png"),
	sprites = {
		idle 	= quad(0, 0, 48, 48),
		walk1 	= quad(48, 0, 48, 48),
		walk2   = quad(96, 0, 48, 48),
		walk3   = quad(144, 0, 48, 48)
	},
	state = nil,
	x = 200,
	y = 200
}

function _init()
	set_title("Lit - Testing API")
end

function _draw()
	print("Wow it works!", 20, 20, COL_LIGHT_GREEN)
	draw(player.image, player.x, player.y)
	rect(50, 50, 40, 40, COL_ORANGE)
	rect(75, 75, 40, 40, COL_LIGHT_GREEN, 128)
	rect(100, 100, 40, 40, COL_BLUE_GRAY, 128)
end