xSemaphoreHandle xMutex;  //互斥资源
int num = 0;

//创建任务1
TaskHandle_t handle1;
//int param = 30;

void loop1(void* param) {
  while (1) {
    delay(500);
    int core = xPortGetCoreID();  //获取当前核
    Serial.print("******");
    Serial.print("loop1:");
    Serial.print(core);
    Serial.println("******");
    if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
      num++;
      xSemaphoreGive(xMutex);
    }
  }
}
void setup() {
  Serial.begin(115200);
  xMutex = xSemaphoreCreateMutex();
  xTaskCreatePinnedToCore(loop1, "task1", 2048, NULL, 15, &handle1, 0);
}

void loop() {
  delay(1200);
  int core = xPortGetCoreID();  //获取当前核
  Serial.print("core:");
  Serial.print(core);
  if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
    Serial.print(" num:");
    Serial.println(num);
    xSemaphoreGive(xMutex);
  }
}
