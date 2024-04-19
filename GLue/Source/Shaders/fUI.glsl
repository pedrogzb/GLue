#version 330 core

in vec3 vPos;
in vec2 TexCoord;
out vec4 FragColor;
uniform float FrameRate;
uniform int   opcion;



vec2 remap(vec2 p, out int ID){
    p.x *= 16.;
    p.y *= 8.;
    
    if(p.x > 4. || p.y > 8.) p = vec2(-1.);
    if(p.x < 0. || p.y < 0.) p = vec2(-1.);
    
    ID =  int(floor(p.x) + 4.*floor(p.y));
    
    p = fract(p);
    return p;
}

void main() {
    const int nums[14] = int[](0x69db9996,
                               0x46444444,
                               0x6984211f,
                               0x69848896,
                               0x4215f444,
                               0xf1178896,
                               0x69179996,
                               0xf8844222,
                               0x69969996,
                               0x6999e896,
                               0x00000000,
                               0xf1171111,
                               0x79997111,
                               0x69168896);

    int display[7] = int[](0,0,0,10,11,12,13);
    display[0] = int(mod(FrameRate/1e3,10.));
    if(display[0] == 0) display[0] = 10;
    display[1] = int(mod(FrameRate/1e2,10.));
    display[2] = int(mod(FrameRate/1e1,10.));
    display[3] = int(mod(FrameRate/1e0,10.));

    vec3 col = vec3(0.2,0.3,0.3);
    for(float i = 0.0; i < 7.;++i){
        int ID;
        float size = 2.;
        vec2 F = TexCoord - vec2((i*2.)/(7.5*size)+0.01,0.5/size);
        if( i >= 4.0) F.x -= 0.04;
        F *= size;
        vec2 uv = remap(F, ID);
        vec3 mask;
        switch(opcion){
            case 1:
                uv  = abs(uv*2.-1.); 
                mask = 2.*vec3(step(length(uv),1.));
                break;
            case 2:
                mask = 2.*vec3(ceil(uv.y*uv.x));
                break;
            case 3: 
                mask = vec3(ceil(uv.y+uv.x));
                break;
            case 4: 
                mask = 4.*vec3(uv.y*uv.y);
                break;
            case 5: 
                mask = 4.*vec3(uv.x*uv.x);
                break;
            case 6: 
                mask = 50.*vec3(uv.x*(1.-uv.x)*uv.y*(1.-uv.y));
                break;
        }

        int num = nums[display[int(i)]];
        if(((num >> ID)& 0x01) == 1) col = mix(col,vec3(.3,.3,.7),mask);
    }
    FragColor = vec4(col,1.0);
}