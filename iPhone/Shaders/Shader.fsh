//
//  Shader.fsh
//  sample
//
//  Created by alexey on 1/4/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
	gl_FragColor = colorVarying;
}
