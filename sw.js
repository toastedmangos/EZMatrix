self.addEventListener("install", event => {
  event.waitUntil(
    caches.open("matrix-drawer-cache").then(cache => {
      return cache.addAll([
        "./",
        "./index.html",
        "./manifest.json",
        "./icon.png"
      ]);
    })
  );
});

self.addEventListener("fetch", event => {
  event.respondWith(
    caches.match(event.request).then(cached => cached || fetch(event.request))
  );
});
