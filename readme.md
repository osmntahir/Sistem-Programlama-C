# Komut İşleme Projesi

Bu proje, veri dosyasından okunan komutlara göre çıkış dosyası oluşturan bir programı C dilinde geliştirmeyi amaçlamaktadır.

## Proje Açıklaması

Bu projede, belirli komutları içeren bir giriş dosyasını okuyarak, çıkış dosyasını oluşturan bir program geliştirilmektedir. Proje, C dilinde yazılmaktadır ve giriş, çıkış ve dosya işlemleri için "libfdr" kütüphanesi kullanılmaktadır.

## Komutlar ve Özel Karakterler

Proje, aşağıdaki komutları ve özel karakterleri içermektedir:

- `yaz:`: Belirli karakterleri belirli sayıda çıktı dosyasına yazdırır.
- `sil:`: Belirli karakterleri belirli sayıda geriye doğru tarayarak çıktı dosyasından siler.
- `sonagit:`: Çıktı dosyasının sonuna gider.
- `dur:`: Tüm komutların icrasından oluşan veriyi çıktı dosyasına yazar ve programdan çıkılır.
- Özel karakterler: `\b` (boşluk), `\n` (yeni satır).

## Kullanım

Program, komut satırından giriş ve çıkış dosyalarının adlarını alır. Eğer bu dosyaların isimleri verilmezse, program kullanıcıyı uyarır veya öntanımlı dosya isimlerini kullanır.

Örnek kullanım:

```sh
./program girdi_dosyasi.txt cikti_dosyasi.txt
```

## İçerik

Proje dosyaları şu şekildedir:

1. `main.c`: Ana program dosyası.
2. `dllist.c`, `dllist.h`: Çift yönlü bağlı liste yapıları ve fonksiyonları.
3. `libfdr` klasörü: libfdr kütüphanesi dosyaları.
4. `Makefile`: Proje dosyalarının derlenmesi ve çalıştırılabilir dosyayı oluşturmak için kullanılır.
5. `README.md`: Proje hakkında genel bilgiler ve kullanım talimatları içerir.

## Geliştiriciler

- Osman Tahir Özdemir 


    
