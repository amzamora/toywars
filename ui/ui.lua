local ui = {}

function ui.Button(parent, x, y, width, height, label, onclick)
	local released = 1
	local pressed = 2

	local node = {}
	node.x = x
	node.y = y
	node.width = width
	node.height = height
	node.label = label
	node.state = released
	node.parent = parent

	node.draw = function()
		local pos = nodeToGlobalPos(node, node.x, node.y)

		if node.state == released then
			love.graphics.setColor(0, 0, 0)
			drawRectangle("fill", pos.x, pos.y, node.width, node.height)

			love.graphics.setColor(0.7, 0.7, 0.7)
			drawRectangle("fill", pos.x, pos.y - node.height / 2.0, width, 8)

			love.graphics.setColor(1, 1, 1)
			drawText(fonts["Romulus"], node.label, pos.x, pos.y)

		else
			love.graphics.setColor(0, 0, 0)
			drawRectangle("fill", pos.x, pos.y - 8, node.width, node.height)

			love.graphics.setColor(0.7, 0.7, 0.7)
			drawRectangle("fill", pos.x, pos.y + node.height / 2.0 - 4, node.width, 8)

			love.graphics.setColor(1, 1, 1)
			drawText(fonts["Romulus"], node.label, pos.x, pos.y - 8)
		end
	end

	node.mousepressed = function(x, y, mouseButton, istouch, presses)
		local pos = nodeToGlobalPos(node, node.x, node.y)
		pos = toScreenCoordinates(pos.x, pos.y)

		if mouseButton == 1
		and math.abs(x - pos.x) <= node.width / 2.0
		and math.abs(y - pos.y) <= node.height / 2.0 then
			node.state = pressed
			soundEffects["button_click"]:play()
		end
	end

	node.mousereleased = function(x, y, mouseButton, istouch)
		local pos = nodeToGlobalPos(node, node.x, node.y)
		pos = toScreenCoordinates(pos.x, pos.y)

		if mouseButton == 1
		and node.state == pressed then
			node.state = released
			if math.abs(x - pos.x) <= node.width / 2.0
			and math.abs(y - pos.y) <= node.height / 2.0 then
				if onclick ~= nil then
					onclick()
				end
			end
		end
	end

	return node
end

function ui.RoundButton(parent, x, y, radius, label, onclick)
	local released = 1
	local pressed = 2

	local node = {}
	node.x = x
	node.y = y
	node.radius = radius
	node.label = label
	node.state = released
	node.parent = parent

	node.draw = function()
		local pos = nodeToGlobalPos(node, node.x, node.y)

		if node.state == released then
			love.graphics.setColor(0, 0, 0)
			drawCircle("fill", pos.x, pos.y, node.radius)

			love.graphics.setColor(1, 1, 1)
			drawText(love.graphics.newFont(36), node.label, pos.x, pos.y + 2)

		else
			love.graphics.setColor(0.8, 0.8, 0.8)
			drawCircle("fill", pos.x, pos.y, node.radius)

			love.graphics.setColor(1, 1, 1)
			drawText(love.graphics.newFont(36), node.label, pos.x, pos.y + 2)
		end
	end

	node.mousepressed = function(x, y, mouseButton, istouch, presses)
		local pos = nodeToGlobalPos(node, node.x, node.y)
		pos = toScreenCoordinates(pos.x, pos.y)

		if mouseButton == 1
		and distanceBetween(pos.x, pos.y, x, y) <= node.radius then
			node.state = pressed
			soundEffects["button_click"]:play()
		end
	end

	node.mousereleased = function(x, y, mouseButton, istouch)
		local pos = nodeToGlobalPos(node, node.x, node.y)
		pos = toScreenCoordinates(pos.x, pos.y)

		if mouseButton == 1
		and node.state == pressed then
			node.state = released
			if distanceBetween(pos.x, pos.y, x, y) <= node.radius then
				if onclick ~= nil then
					onclick()
				end
			end
		end
	end

	return node
end


function ui.makeCard(parent, x, y, image)
	local node = {}
	node.x = x
	node.y = y
	node.image = image
	node.player = player
	node.tank = {}
	node.tank.attack = 1
	node.tank.life = 1
	node.tank.range = 1
	node.tank.speed = 1
	node.parent = parent
	local width = 128
	local height = 256

	node.children = {}
	table.insert(node.children, ui.RoundButton(node, -width / 2.0, height / 2.0, 20, "x"))

	node.update = function(dt)
	end

	node.draw = function()
		local pos = nodeToGlobalPos(node, node.x, node.y)
		love.graphics.setColor(0, 0, 0)
		drawRectangle("line", pos.x, pos.y, width, height)

		love.graphics.setColor(1, 1, 1)
		local spriteWidth = width - 20
		drawSprite("tank", pos.x, pos.y + width /2.0, spriteWidth, spriteWidth)

		love.graphics.setColor(0, 0, 0)
		drawLine(pos.x - width / 2.0, pos.y, pos.x + width / 2.0, pos.y)

		for i, node in ipairs(node.children) do
			node.draw()
		end
	end

	return node
end

return ui
