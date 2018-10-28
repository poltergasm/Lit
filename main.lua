local t_tick  = 0
local counter = 500
local txt
local player = {x=60, y=200}
local enemy  = {x=120, y=200}

function _init()
	lit.win.set_title("Lit Demo")
	--lit.win.fullscreen(true)
	player.sprite = lit.gfx.image("assets/player.png")
	enemy.sprite  = lit.gfx.image("assets/goomba.png")
	enemy.sprite_flipped = lit.gfx.image_flip_x(enemy.sprite)
end

function _update(dt)
	local gt = lit.timer.get_time()
	if gt > t_tick+0.5 and counter > 0 then
		t_tick = lit.timer.get_time()
		counter = counter - 1
		txt = "Timer: " .. counter
	end
end

function _draw()
	-- a random rect, because fuck you that's why
	lit.gfx.rect(lit.win.get_width() - 100, 0, 100, 90, COL_DARK_RED)

	-- draw the hud background
	lit.gfx.rect(0, 0, lit.win.get_width(), 40, COL_DARK_GRAY, 150)

	-- add a shadow to make it look pretty
	lit.gfx.print(txt, 12, 7, COL_BLACK)
	lit.gfx.print(txt, 10, 5, COL_WHITE)

	-- draw our shitty looking player
	lit.gfx.draw(player.sprite, player.x, player.y)

	-- draw another sprite
	lit.gfx.draw(enemy.sprite, enemy.x, enemy.y)
end