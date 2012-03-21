
density_ve   = 12.0
nickel_sigma = 10.0


function density( x, y, z )
    r = math.sqrt( x * x + y * y + z * z )
    return 10.0 * math.exp( - r / density_ve  )
end

function nickel( x, y, z )
    r = math.sqrt( x * x + y * y + z * z )
    return 1.0 * math.exp( - 0.5 * r * r / nickel_sigma / nickel_sigma )
end
