bool runningText() {
    unsigned long now = millis();
    if (now - lastMove < SCROLL_INTERVAL) return false;
    lastMove = now;
    pos1--;
    pos2--;
    if (pos1 < -textWidth1) pos1 = AREA_WIDTH;
    if (pos2 < -textWidth2) pos2 = AREA_WIDTH;
    runningtext1.clear(FansElectronics_Bitmap::Black);
    runningtext2.clear(FansElectronics_Bitmap::Black);
    runningtext1.drawText(pos1, 0, textatas.c_str());
    runningtext2.drawText(pos2, 0, textbawah.c_str());
    dmd.drawBitmap(0, 0, runningtext1, FansElectronics_Bitmap::White);
    dmd.drawBitmap(DISPLAY_WIDTH - AREA_WIDTH, 0, runningtext2, FansElectronics_Bitmap::White);
    return true;
}

int get_h_graph(int value){
    int result = 0;
    if(value > 300) result = map(value, 301, 500, 78, 96);
    else if(value > 100) result = map(value, 101, 300, 39, 77);
    else result = map(value, 0, 100, 0, 38);
    return result;
}

bool drawGraph() {
    static unsigned long lastGraph = 0;
    unsigned long now = millis();
    if (now - lastGraph < 100) return false;

    lastGraph = now;

    h_pm10 = constrain(get_h_graph(pm10.toInt()), 0, 96);
    h_pm25 = constrain(get_h_graph(pm25.toInt()), 0, 96);
    h_so2  = constrain(get_h_graph(so2.toInt()), 0, 96);
    h_co   = constrain(get_h_graph(co.toInt()), 0, 96);
    h_o3   = constrain(get_h_graph(o3.toInt()), 0, 96);
    h_no2  = constrain(get_h_graph(no2.toInt()), 0, 96);
    h_hc   = constrain(get_h_graph(hc.toInt()), 0, 96);

    dmd.fill(192, 0, 7 * 96, 16,FansElectronics_Bitmap::Black);
    int graphValues[7] = {h_pm10,h_pm25,h_so2,h_co,h_o3,h_no2,h_hc};
    for (int i = 0; i < 7; i++) {
        int graphX = 192 + (i * 96);
        int barWidth = graphValues[i];
        dmd.fill(graphX + (96 - barWidth),0,barWidth,16,FansElectronics_Bitmap::White);
    }
    return true;
}