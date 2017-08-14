

--pre to after
function pre2after(pre, line, rate, minus)
	return (pre - line)*rate - minus
end

--after to pre
function after2pre(after, line, rate, minus)
	return (after - minus - rate * line) / (1 - rate)
end

--pre to after
function tax2pre(tax, line, rate, minus)
	return (tax + minus) / rate + line
end

avg, sum = average(10, 20, 30, 40, 50)