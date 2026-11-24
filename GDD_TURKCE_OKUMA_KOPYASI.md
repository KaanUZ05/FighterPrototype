# FighterPrototype — Oyun Tasarım Dokümanı (Türkçe okuma kopyası)

**Sürüm:** 1.0 · **Tarih:** 25 Kasım 2026 · **Teknik kaynak:** `docs/01_VISION_AND_GDD.md` (Codex için bağlayıcı İngilizce sürüm). Bu Türkçe kopya, oyunun kapsamını kontrol edebilmen ve yaratıcı kararları onaylayabilmen içindir.

## 1. Oyun ne olacak?

Unreal Engine 5.9 kullanılarak geliştirilen, iki orijinal 3D dövüşçünün tek bir düzlem üzerinde karşılaştığı, karanlık ve sinematik atmosferli **2.5D yerel dövüş oyunu**. İlk amaç AAA ölçekte bir Mortal Kombat kopyası değil; görsel olarak tutarlı, iyi hissettiren, tamamlanmış bir **iki karakterli oynanabilir demo**. Ticari isim `FighterPrototype` değil; o proje adımız.

İlk demo: Windows, yerel iki oyunculu 1v1, 2 karakter, 1 arena, aynı ekranda tek kamera, can barları ve raund saati, 2 galibiyete ulaşınca maç sonu, rematch, her karakterde 4 temel normal saldırı ve 2 özgün special. Basit karakter seçme ekranı, dövüş VFX/sesleri ve orijinal animasyonları içerir. Sinematik bitirişler **opsiyonel son aşama**dır; kreatif onayın olmazsa oyunu bitirmeyi engellemez.

## 2. En önemli ve değiştirilemez karakter kuralımız

İki dövüşçünün **tüm temel oynanış özellikleri aynıdır:** maksimum can, ileri/geri hız, ivme, zıplama, yerçekimi, normal saldırı hasarı, menzil, hitbox, startup/active/recovery frame değerleri, kombo iptal pencereleri, blok ve hitstun kuralları. Yalnızca karakterlere özgü **special move'lar** ve görünüş, kostüm, animasyon stili, özel efektleri farklıdır.

Bu nedenle `FighterA` ve `FighterB` için iki ayrı normal saldırı sistemi yazılmayacak. **Tek bir shared move set** ve **tek bir shared base stats** veri kaynağı kullanılacak. Model daha iri olsa da normal yumruğu daha uzağa ulaşmayacak. Bir karakter zırhlı diye yavaş, diğeri çevik görünüyor diye hızlı olmayacak. Skill animasyonu geçici bir dash içerebilir, ancak normal yürüyüş hızını kalıcı değiştiremez.

## 3. Oynanış ve maç akışı

Oyuncular başlangıçta birbirine bakar. Dövüş sağ-sol ekseninde ilerler; zıplama serbesttir ama arenanın derinliğine gidilemez. Yumruk ve tekmelerin vurabildiği kareler ve hareket sonrası toparlanma süreleri **60 Hz mantıksal combat adımlarına** göre hesaplanır. Animasyon bu mantığı takip eder, oyunun hangi karede hasar verdiğine görsel animasyon tek başına karar vermez.

İlk taslakta 1000 can, 99 saniyelik raund, 2 raund alanın maçı kazanması vardır. Normal saldırılar `LightPunch`, `HeavyPunch`, `LightKick`, `HeavyKick`. Sonradan ortak crouch/jump normal ve kısa bir ortak kombo eklenir. Blok: rakibin aksi yönüne basılı tutmak; aşağı+geri ise alçak blok. Saldırı bölgesi, stun ve geçerli guard davranışı tüm karakterlerde aynı sistemden gelir. Süre biterken eşit canda tarafsızlık için raund tekrar edilir (ayarlanabilir taslak karar).

Başlangıç girişleri: P1 klavye `A/D/W/S`, normal saldırılar `J/K/U/I`, özel hareketler `O/P`; P2 gamepad. Fiziksel ikinci cihaz yoksa geliştirme testlerinde script kontrollü dummy kullanılabilir ancak bu, gerçek iki oyunculu testin geçtiği anlamına gelmez.

## 4. Özel saldırılar — sadece geçici mekanik örnekler

Oyuncu A için kısa mesafe dash-vuruş ve yakın alan darbesi; Oyuncu B için yatay projectile ve gecikmeli alan tuzağı. **Ateş ve buz karakterleri zorunlu değildir.** Henüz karakter isimlerini, kostümlerini, elementlerini veya bu özel hareketlerin nihai tasarımını belirlemiyoruz. Dört special'ın teknik prototipi çalıştıktan sonra sen onaylayabilir, değiştirebilir veya sıfırdan başka fikirler seçebilirsin.

## 5. Grafik ve animasyon üretim yöntemi

Temel mekanikler önce basit mannequin/capsule modellerle geliştirilir. Daha sonra bir sanat rehberi (*Art Bible*) hazırlanır. İki karakter için ayrı ama aynı evrene ait front/side/back konsept çizimleri üretilecek; **her birinin tasarımını sen onaylayacaksın**. Ardından tek bir 3D karakter mesh'i, UV/material, uyumlu iskelet/rig ve kullanılabilir animasyon seti üretilecek. Her yumruk için ayrı AI görseli çizdirmek yerine 3D model üzerinden animasyon oynatılacak. Mesh/rig kalitesini manuel kontrol etmeden üretime hazır kabul etmeyeceğiz.

Hedef özgün, karanlık, sinematik ve stilize-gerçekçi bir atmosfer; fotogerçekçilik zorunlu değil. Normal saldırıların frame ve hitboxları 3D karakterin vücut ölçüsüne göre değişmeyecek. Bitirişlerde gereksiz şiddet/gore varsaymıyoruz; tonunu sonradan sen belirleyeceksin.

## 6. Yazılım mimarisi

C++ dövüş mantığını, GameMode/State raund yönetimini, Enhanced Input iki oyuncunun kontrollerini, ortak Data Asset'ler temel istatistikleri ve normal hareketleri, Blueprint/Animation Blueprint sunumu, Niagara görsel efektleri, UMG arayüzü yönetecek. Codex editöre Unreal MCP üzerinden bağlanacak ve her görevi ayrı tamamlayacak.

Her alt görevde şunlar zorunlu: önce dosyaları ve mevcut durumu inceleme, küçük değişiklik, gerçek derleme/test, `PASS/FAIL/NOT RUN` ayrımı, `reports/TASK_###_RESULT.md` sonuç raporu, ardından **otomatik olarak sonraki göreve geçmeden durma**.

## 7. Kapsam dışındaki işler

Online matchmaking, rollback netcode, tam story mode, konsol sürümleri, para kazanma sistemi, onlarca dövüşçü, yüzlerce sinematik ve başka oyun modları ilk sürüme dahil değil. Bunlar sonradan yeni bir yol haritası ile ele alınabilir.

## 8. Senin onaylayacağın yaratıcı kararlar

Oyun dünyasının kesin tarzı, iki karakterin isim/kostüm/özgün görünüşleri, dört özel hareketin nihai seti, arenanın detayları ve isteğe bağlı finisher'ların koreografisi. Bunları ilk sprintte seçmek gerekmez; plan ilgili aşamalarda senden onay ister.

## 9. Başarı kriterimiz

Unreal Editor olmadan çalıştırılabilen bir Windows demosunda iki kişi dövüşebilir; temel özellikler birebir eşittir; normal saldırılar ve savunma doğru çalışır; her karakter iki farklı skill kullanır; can/raund/timer/HUD ve rematch tamamlanır; tutarlı iki 3D model ve animasyonlar görülür; yapılanların derleme, test ve görsel kanıtları kaydedilir. İlk demo güzel görünmekle kalmayıp **oynanabilir bir dövüş oyunu gibi hissettirmelidir**.
