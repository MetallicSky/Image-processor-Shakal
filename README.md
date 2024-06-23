# Обработчик изображений "Шакал"

Программа делит изображение на треугольные сегменты на основе входящих в них пикселей - если найдутся два с чересчур отличными цветами, то сегмент делится на две части и так далее, пока таких пикселей не найдется или узел не достигнет минимально возможного размера.

![image](https://github.com/MetallicSky/Image-processor-Shakal/assets/46136189/674526c2-3c69-4457-8d42-10f32d5a24ae)

Допустимое максимальное отклонение в цвете пикселей настраивается с помощью слайдера.

![image](https://github.com/MetallicSky/Image-processor-Shakal/assets/46136189/f3e12381-a954-4448-a1c9-b8f4550489b2)
![image](https://github.com/MetallicSky/Image-processor-Shakal/assets/46136189/3577a94a-0170-400c-a687-e724a0245bbb)

Минимальный размер сегмента также настраивается.

![image](https://github.com/MetallicSky/Image-processor-Shakal/assets/46136189/b48041aa-74f0-4670-8f4d-eeb98b117fd9)

Для подробного рассмотрения результатов работы присутствует функция зума. Отображаемый фрагмент изображения синхронизируется между тремя окнами.

![image](https://github.com/MetallicSky/Image-processor-Shakal/assets/46136189/fe984cb0-8580-4e9f-b73a-aeeba0709f09)

Также присутствует версия (Shakal 3) с делением фрагментов на прямоугольники и небольшими другими изменениями.

![image](https://github.com/MetallicSky/Image-processor-Shakal/assets/46136189/b76df013-f846-4a6b-b540-86b83b7d7487)

Функция ЧБ режима, уменьшая диапозон цветов, влияет на итоговое количество сегментов.

![image](https://github.com/MetallicSky/Image-processor-Shakal/assets/46136189/36cb311b-22a0-4d27-ba27-c14292ef18c5)
