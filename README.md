# adam-asmaca
# Kelime Bulmaca - Adam Asmaca 🎮

Bu proje, C programlama dili kullanılarak geliştirilmiş terminal tabanlı klasik bir Adam Asmaca oyunudur. Kullanıcıların kelime dağarcığını test ederken eğlenceli vakit geçirmelerini sağlamak amacıyla tasarlanmıştır.

##  Özellikler

*   **Dinamik Kategori Sistemi:** Oyun; Meslekler, Meyveler, Şehirler ve Ülkeler olmak üzere 4 farklı kategori seçeneği sunar.
*   **Dosyadan Okuma:** Kelimeler kod içine gömülmek yerine doğrudan `meslekler.txt`, `meyveler.txt`, `sehirler.txt` ve `ulkeler.txt` dosyalarından dinamik olarak okunur.
*   **Puanlama Sistemi:** Yapılan her doğru harf tahmininde +10 puan kazanılırken, yanlış tahminlerde -5 puan düşülür.
*   **Rekor Takibi:** Oyun bitiminde elde edilen skor, tüm zamanların en yüksek skoru ile karşılaştırılır ve rekor kırılırsa `rekor.txt` dosyasına kaydedilerek güncellenir. Mevcut kayıtlı rekor 40 puandır.
*   **Hata Kontrolü:** Oyuncunun toplam 6 yanlış harf girme hakkı vardır ve her hatada darağacı adımları ekrana çizilir. Ayrıca daha önce girilen harfler hafızada tutularak oyuncunun aynı harfi tekrar girmesi engellenir.

##  Kullanılan Teknolojiler

*   C Programlama Dili
*   Dosya İşlemleri (File I/O)

##  Kurulum ve Çalıştırma

Projeyi kendi bilgisayarınızda derleyip çalıştırmak için aşağıdaki adımları izleyebilirsiniz.

1. **Depoyu Klonlayın veya İndirin:**
   Proje dosyalarını bilgisayarınıza indirin.

2. **Derleme:**
   Terminal veya komut satırını açarak proje dizinine gidin ve aşağıdaki komutla kodları derleyin:
   ```bash
   gcc main.c -o oyun
Derleme işlemi bittikten sonra oyunu başlatmak için şu komutu girin:
 ./oyun
   
