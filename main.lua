local t_tick  = 0
local counter = 500
local txt

function _init()
	lit.win.set_title("Counting in seconds")
	lit.gfx.set_bg(COL_DARK_GRAY)
end

function _update(dt)
	local gt = lit.timer.get_time()
	if gt > t_tick+1 and counter > 0 then
		t_tick = lit.timer.get_time()
		counter = counter - 1
		txt = "Timer: " .. counter
	end
end

function _draw()
	-- let's add a shadow to make it look pretty
	lit.gfx.print(txt, 34, 64, COL_BLACK)
	lit.gfx.print(txt, 30, 60, COL_WHITE)
end