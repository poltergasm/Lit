local player = {
	img = image("assets/player_s.png"),
	anim = {
		idle 	= { quad(0, 0, 48, 48) },
		walk 	= {
			quad(48, 0, 48, 48),
			quad(96, 0, 48, 48),
			quad(144, 0, 48, 48)
		}
	},
	state = "walk",
	x = 200,
	y = 200,
	tick = 0,
	frame = 0,
	step = 7 -- animation speed
}

function _init()
	set_title("Lit - Testing API")
end

function _update(dt)
	player.tick=(player.tick+1)%player.step
    if (player.tick == 0) then
      player.frame = player.frame%#player.anim[player.state]+1
      player.chunk = player.anim[player.state][player.frame]
    end
end

function _draw()
	print("Wow it works!", 20, 20, COL_LIGHT_GREEN)
	draw(player.img, player.x, player.y, player.chunk)
	rect(50, 50, 40, 40, COL_ORANGE)
	rect(75, 75, 40, 40, COL_LIGHT_GREEN, 128)
	rect(100, 100, 40, 40, COL_BLUE_GRAY, 128)
end