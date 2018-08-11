$fn=80;

module noCornersCube(width, height, depth, cornerRadius) {
    
    //cube([width, height, depth]);
    union() {
        linear_extrude(height=depth) {
            // Square with corners cut.
            polygon([
            [cornerRadius,0],
            [width-cornerRadius, 0],
            [width, cornerRadius],
            [width, height-cornerRadius],
            [width-cornerRadius, height],
            [cornerRadius, height],
            [0, height-cornerRadius],
            [0, cornerRadius],
            [cornerRadius,0]
            ]);
        }
        
    }
}

module roundedCube(width, height, depth, cornerRadius) {
    
    //cube([width, height, depth]);
    union() {
        translate([cornerRadius,cornerRadius,0]) {
            cylinder(r=cornerRadius, h=depth);   
        }
        translate([width-cornerRadius,cornerRadius,0]) {
            cylinder(r=cornerRadius, h=depth);
        }
        translate([cornerRadius,height-cornerRadius,0]) {
            cylinder(r=cornerRadius, h=depth);
        }
        translate([width-cornerRadius,height-cornerRadius,0]) {
            cylinder(r=cornerRadius, h=depth);
        }
        
        noCornersCube(width, height, depth, cornerRadius);
    }
}

height = 23;

module mountingPad(x,y) {
    translate([x,y,0]) {
        difference() {
            union() {
                cylinder(d=5, h=height);
            }
            union() {
                cylinder(d=1.8, h=height+1);
            }
        }
    }
}

module mountingHole(x,y) {
    translate([x,y,0]) {
        #cylinder(d=1.8, h=height);
        //cylinder(d=2.5, h=8);
    }
}

wallWidth = 1;

difference() {
    union() {
        roundedCube(97.5, 25, height, 2);
    }
    union() {
        translate([wallWidth, wallWidth, wallWidth+0.01]) {
            roundedCube(97.5-(2*wallWidth), 25-(2*wallWidth), height-wallWidth, 2);
        }
        
        // mounting holes need a little extra clearance
        translate([0, 0, 2]) {
            mountingHole(2.5, 2.5);
            mountingHole(2.5, 22.5);

            mountingHole(95, 2.5);
            mountingHole(95, 22.5);
        }
        
        // Space for esp8266
        translate([18, 0, height-0.8]) {
            #cube([17,25,0.9]);
        }
        
        translate([18, 0, height-3.4]) {
            #cube([17,15,3.5]);
        }
        
        // tant cap
        translate([44.8, 19, height-5]) {
            #cube([4,6,5]);
        }
        
        
    }
}

mountingPad(2.5, 2.5);
mountingPad(2.5, 22.5);

mountingPad(95, 2.5);
mountingPad(95, 22.5);
