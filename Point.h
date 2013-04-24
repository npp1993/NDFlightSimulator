//
//  Point.h
//
//  Created by Nathaniel Pawelczyk on 4/22/13.
//  Copyright (c) 2013 Nathaniel Pawelczyk. All rights reserved.
//

#ifndef Point_H
#define Point_H

class Point {
	
	public:
		int x;
		int y;
		static int const tileSize = 1;
		
		Point(int a, int b)
		{
			x = a;
			y = b;
		}

};

#endif