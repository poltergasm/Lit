
local text
local rx,ry = 42, 45
local selected = "song1"
local sng1,sng2

function _init()
	text = "Not playing"
	sng1 = snd("assets/audio/song1.mp3", true)
	sng2 = snd("assets/audio/song2.mp3", true)
	menuchange = snd("assets/audio/menu_move.wav")
	menuselect = snd("assets/audio/menu_select.wav")
	selected = sng1
end

function _update(dt)
	if btnp(KEY_DOWN) then
		rx,ry = 42, 95
		selected = sng2
		snd_play(menuchange)
	end
	if btnp(KEY_UP) then
		rx,ry = 42, 45
		selected = sng1
		snd_play(menuchange)
	end
	if btnp(KEY_X) then
		snd_play(selected)
		snd_play(menuselect)
	end
end

function _draw()
	set_bg(COL_BLACK)
	rect(rx, ry, 142, 42, COL_LIGHT_GREEN)
	print("Play song 1", 52, 52, COL_BLACK)
	print("Play song 1", 50, 50, COL_WHITE)
	
	print("Play song 2", 52, 102, COL_BLACK)
	print("Play song 2", 50, 100, COL_WHITE)

end