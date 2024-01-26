import { AfterViewInit, Component, Inject, OnInit, PLATFORM_ID } from '@angular/core';
import { Router } from '@angular/router';
import { ScrollService } from '../../../../services/scroll.service';
import AOS from 'aos';
import 'aos/dist/aos.css';
import { isPlatformBrowser } from '@angular/common';

@Component({
  selector: 'app-dariel',
  standalone: true,
  imports: [],
  templateUrl: './dariel.component.html',
  styleUrl: './dariel.component.css',
})
export class DarielComponent implements AfterViewInit, OnInit {
  constructor(
    @Inject(PLATFORM_ID) private platformId: Object,
    private router: Router,
    private scrollService: ScrollService
  ) {}
  ngOnInit(): void {
    if (isPlatformBrowser(this.platformId)) {
      AOS.init();
    }
  }
  ngAfterViewInit() {
    this.scrollService.scrollObservable.subscribe((section) => {
      setTimeout(() => {
        this.scrollToElement(section);
      }, 0);
    });
  }

  navigateAndScroll(): void {
    this.scrollService.scrollTo('darielAnchor');
    this.router.navigate(['']);
  }

  scrollToElement(section: string) {
    document
      .getElementById(section)
      ?.scrollIntoView({ behavior: 'smooth', inline: 'start', block: 'start' });
  }
}
