local t_tick  = 0
local counter = 500
local txt

function _init()
	lit.win.set_title("Counting in seconds")
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
	-- draw the hud background
	lit.gfx.rect(0, 0, 800, 40, COL_DARK_GRAY)

	-- a random rect, because fuck you that's why
	lit.gfx.rect(700, 0, 100, 80, COL_DARK_RED)

	-- add a shadow to make it look pretty
	lit.gfx.print(txt, 14, 9, COL_BLACK)
	lit.gfx.print(txt, 10, 5, COL_WHITE)
end