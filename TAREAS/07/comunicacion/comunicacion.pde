import  processing.serial.*;
Serial aport;
PImage photo;
PImage photo2;
int l = 0;
int v =0;
int num = 20;
int puerto;
float pos =0;
float mx[] = new float[num];
float my[] = new float[num];

void setup(){
 aport = new Serial(this, "COM3", 9600);
  size(900, 400);
  photo = loadImage("logouv.jpg");
   photo2 = loadImage("instru.png");
  noStroke();
  fill(255, 153); 
  
}
void draw(){
  background(0);
  while (aport.available() > 0) {       // Consulta si hay un byte disponible en el puerto
    puerto = aport.read(); 
    pos=map(puerto,10,160,412,792);
  }
  photo.resize(70, 80);
  image(photo, 0, 0);
   photo2.resize(70, 80);
  image(photo2, 80, 0);
  fill(#FFFFFF);
   textSize(50);
  text("EQUIPO NUMERO 6",180,50);
  if((mouseX > 180) && (mouseX < 285) && (mouseY > 280) && (mouseY < 320)){
     fill(#20CB15);
  if(mousePressed){
    fill(#0EE000);
    aport.write('e');
    l = 1;
  }
  }
  else{
     fill(#13830C);
  } 
   rect(180, 280, 105, 40, 8); 
   
   fill(#FFFFFF);
   textSize(20);
   text("ON", 215, 350);
  
  
   if((mouseX > 40) && (mouseX < 145) && (mouseY > 280) && (mouseY < 320)) {
     fill(#C91616);
  if(mousePressed){
    fill(#DE2C00);
    aport.write('a');
    l=0;
  }
  }
  else{
     fill(#810D0D);
  }
 rect(40, 280, 105, 40, 8);
 
 fill(#FFFFFF);
 textSize(20);
 text("OFF", 70, 350);
 
 if(l==1){
   fill(#FFFFFF);
   textSize(30);
   text("Estado del led: Encendido", 0, 200);
   
 }
 else{
   fill(#FFFFFF);
   textSize(30);
   text("Estado del led: Apagado", 0, 200);
   
 }
  if(puerto > 160){
    v=792;
  }
  else if(puerto < 10){
   v=412;
  }
  else {
    
    v=int(pos);
  }
  int which = frameCount % num;
  mx[which] = v;
  my[which] = 255;
  
  for (int i = 0; i < num; i++) {
    // which+1 is the smallest (the oldest in the array)
    int index = (which+1 + i) % num;
    ellipse(mx[index], my[index], i, i);
  }
  noFill();
  strokeWeight(4);
  stroke(#FFFFFF);
     rect(400, 240, 404, 30, 13 );
    if(puerto > 159){
      fill(#11E000);
       textSize(30);
   text("Objeto fuera de rango", 440, 200);
   }
   else{
     fill(#DEDBDB);
      textSize(30);
   text("Distancia al objeto "+puerto+"cm", 410, 200);
   }
  
   if(puerto < 10){
     fill(#FF0505);
   textSize(40);
   text("¡OBJETO DEMASIADO CERCA!", 310, 350);
   }
}
